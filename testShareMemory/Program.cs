using System;
using System.Collections.Generic;
using System.IO.MemoryMappedFiles;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace testShareMemory
{
    internal class Program
    {
        static String NAME = "shared_memory";
        static void run_server()
        {
            using (MemoryMappedFile mmf = MemoryMappedFile.CreateNew(NAME, 1024))
            {
                using (MemoryMappedViewStream p = mmf.CreateViewStream())
                {
                    string s = DateTime.Now.ToString("o");
                    byte[] b = Encoding.ASCII.GetBytes(s);
                    p.Write(b, 0, b.Length);
                    System.Console.WriteLine("Press any key to terminate ...");
                    System.Console.ReadKey();
                }
            }
        }

        static void run_client() 
        {
            using (MemoryMappedFile mmf = MemoryMappedFile.OpenExisting(NAME))
            {
                using (MemoryMappedViewStream p = mmf.CreateViewStream())
                {
                    if (p.CanRead)
                    {
                        byte[] buf = new byte[64];
                        p.Read(buf, 0, 64);
                        string s = System.Text.Encoding.Default.GetString(buf);
                    }
                }
            }
        }

        static void Main(string[] args)
        {
            System.Configuration.Install.InstallContext _args = new System.Configuration.Install.InstallContext(null, args);
            if (_args.IsParameterTrue("server"))
            {
                run_server();
            }
            else if(_args.IsParameterTrue("client"))
            {
                run_client();
            }
        }
    }
}
