using System;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.Reflection;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Windows.Forms;

internal static class Standalone {
    private static bool Within(string file, string root) {
        return Path.GetFullPath(file).StartsWith(Path.GetFullPath(root).TrimEnd(Path.DirectorySeparatorChar)+Path.DirectorySeparatorChar,StringComparison.OrdinalIgnoreCase);
    }
    private static string Quote(string argument) {
        var result=new StringBuilder("\"");int slashes=0;
        foreach(char c in argument) {
            if(c=='\\'){slashes++;continue;}
            if(c=='\"'){result.Append('\\',slashes*2+1);result.Append(c);}
            else {result.Append('\\',slashes);result.Append(c);}
            slashes=0;
        }
        result.Append('\\',slashes*2);result.Append('"');return result.ToString();
    }
    [STAThread]
    public static int Main(string[] args) {
        AppContext.SetSwitch("Switch.System.IO.UseLegacyPathHandling",false);
        AppContext.SetSwitch("Switch.System.IO.BlockLongPaths",false);
        bool test=Array.IndexOf(args,"--self-test")>=0;
        try {
            var assembly=Assembly.GetExecutingAssembly();string expected;
            using(var reader=new StreamReader(assembly.GetManifestResourceStream("Rhine.Payload.sha256")))expected=reader.ReadToEnd().Trim();
            if(expected.Length!=64)throw new InvalidDataException("Invalid runtime checksum");
            string baseDir=Environment.GetEnvironmentVariable("RHINE_RUNTIME_ROOT");
            if(String.IsNullOrWhiteSpace(baseDir))baseDir=Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData),"RhineMusic","runtimes");
            baseDir=Path.GetFullPath(baseDir);Directory.CreateDirectory(baseDir);
            string cache=Path.Combine(baseDir,expected.Substring(0,32)),marker=Path.Combine(cache,".ready");
            using(var mutex=new Mutex(false,"Local\\RhineMusic.Runtime."+expected.Substring(0,24))) {
                bool held=false;
                try {
                    try{held=mutex.WaitOne(TimeSpan.FromMinutes(3));}catch(AbandonedMutexException){held=true;}
                    if(!held)throw new TimeoutException("另一实例正在准备运行时，请稍后重新打开。");
                    bool ready=File.Exists(marker)&&File.ReadAllText(marker).Trim()==expected&&File.Exists(Path.Combine(cache,"electron.exe"))&&File.Exists(Path.Combine(cache,"resources","app","desktop","main.cjs"));
                    if(!ready) {
                        string staging=Path.Combine(baseDir,expected.Substring(0,32)+".part-"+Guid.NewGuid().ToString("N").Substring(0,8));
                        if(!Within(staging,baseDir)||!Within(cache,baseDir))throw new InvalidDataException("Invalid runtime directory");
                        Directory.CreateDirectory(staging);
                        try {
                            using(var payload=assembly.GetManifestResourceStream("Rhine.Payload.zip")) {
                                using(var algorithm=SHA256.Create()) {
                                    string digest=BitConverter.ToString(algorithm.ComputeHash(payload)).Replace("-","").ToLowerInvariant();
                                    if(digest!=expected)throw new InvalidDataException("程序内置运行时校验失败。");
                                }
                                payload.Position=0;
                                using(var zip=new ZipArchive(payload,ZipArchiveMode.Read,true)) {
                                    foreach(var entry in zip.Entries) {
                                        if(entry.FullName=="./"||entry.FullName==".")continue;
                                        string name=entry.FullName.Replace('/',Path.DirectorySeparatorChar);
                                        if(name.IndexOf(':')>=0||Path.IsPathRooted(name))throw new InvalidDataException("Unsafe runtime entry");
                                        string target=Path.GetFullPath(Path.Combine(staging,name));
                                        if(!Within(target,staging))throw new InvalidDataException("Unsafe runtime entry");
                                        if(name.EndsWith(Path.DirectorySeparatorChar.ToString())){Directory.CreateDirectory(target);continue;}
                                        Directory.CreateDirectory(Path.GetDirectoryName(target));
                                        using(var source=entry.Open())using(var destination=new FileStream(target,FileMode.CreateNew,FileAccess.Write,FileShare.None))source.CopyTo(destination);
                                    }
                                }
                            }
                            File.WriteAllText(Path.Combine(staging,".ready"),expected);
                            if(Directory.Exists(cache))Directory.Delete(cache,true);
                            Directory.Move(staging,cache);
                        }finally{if(Directory.Exists(staging)&&Within(staging,baseDir))Directory.Delete(staging,true);}
                    }
                }finally{if(held)mutex.ReleaseMutex();}
            }
            if(Array.IndexOf(args,"--extract-only")>=0)return 0;
            var start=new ProcessStartInfo(Path.Combine(cache,"electron.exe"));
            start.WorkingDirectory=cache;start.UseShellExecute=false;start.CreateNoWindow=true;start.WindowStyle=ProcessWindowStyle.Hidden;
            start.EnvironmentVariables.Remove("ELECTRON_RUN_AS_NODE");
            start.Arguments=Quote(Path.Combine(cache,"resources","app"));
            foreach(string argument in args)start.Arguments+=" "+Quote(argument);
            using(var process=Process.Start(start)){process.WaitForExit();return process.ExitCode;}
        }catch(Exception error) {
            if(test) {
                int index=Array.IndexOf(args,"--report");
                if(index>=0&&index+1<args.Length) {
                    try {string report=Path.GetFullPath(args[index+1]);Directory.CreateDirectory(Path.GetDirectoryName(report));string message=error.ToString().Replace("\\","\\\\").Replace("\"","\\\"").Replace("\r","\\r").Replace("\n","\\n");File.WriteAllText(report,"{\"ok\":false,\"launcherError\":\""+message+"\"}");}catch{}
                }
            }
            if(!test)MessageBox.Show(error.Message,"Rhine Music",MessageBoxButtons.OK,MessageBoxIcon.Error);
            return 1;
        }
    }
}
