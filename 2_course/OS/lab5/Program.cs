using System;
using System.Collections.Generic;
using System.IO;

namespace Bash
{
    class Program
    {
        static double t(string str)
        {
            string[] i = str.Split(".");
            return int.Parse(i[0]) + double.Parse(i[1]) / 10;
        }
        static double f(string str)
        {
            string[] i = str.Split(".");
            if (i.Length == 1)
                return int.Parse(str);
            if(str[str.Length -1] == 'm')
            {
                return double.Parse(i[0]) * 1024;
            }
            else
            {
                return (int.Parse(i[0]) + double.Parse(i[1][0].ToString()) / 10) * 1024 * 1024;
            }
        }
        static void Main(string[] args)
        {
            List<string[]> mas = new List<string[]>();
            using (var sr = new StreamReader("bash.txt"))
            {
                while (!sr.EndOfStream)
                {
                    mas.Add(sr.ReadLine().Split(" ", StringSplitOptions.RemoveEmptyEntries));
                }

            }
            int pid = 4187;
            List<double> Mem_total = new List<double>();
            List<double> Mem_free = new List<double>();
            List<double> Mem_used = new List<double>();
            List<double> Mem_buff_cache = new List<double>();
            List<double> Swap_total = new List<double>();
            List<double> Swap_free = new List<double>();
            List<double> Swap_used = new List<double>();
            List<double> Swap_avail = new List<double>();
            List<int> Virt = new List<int>();
            List<double> Res = new List<double>();
            List<double> Cpu = new List<double>();
            List<double> Mem = new List<double>();
            Dictionary<string, int> valuePairs = new Dictionary<string, int>();
            for (int i = 0; i < mas.Count; i += 9)
            {
                int j = 0;
                if (double.Parse(mas[i + 4][0]) == pid)
                    j = i + 4;
                else if (double.Parse(mas[i + 5][0]) == pid)
                    j = i + 5;
                else if (double.Parse(mas[i + 6][0]) == pid)
                    j = i + 6;
                else if (double.Parse(mas[i + 7][0]) == pid)
                    j = i + 7;
                else if (double.Parse(mas[i + 8][0]) == pid)
                    j = i + 8;
                else break;
                Mem_total.Add(t(mas[i][3]));
                Mem_free.Add(t(mas[i][5]));
                Mem_used.Add(t(mas[i][7]));
                Mem_buff_cache.Add(t(mas[i][9]));
                Swap_total.Add(t(mas[i + 1][2]));
                Swap_free.Add(t(mas[i + 1][4]));
                Swap_used.Add(t(mas[i + 1][6]));
                Swap_avail.Add(t(mas[i + 1][8]));
                Virt.Add(int.Parse(mas[j][4]));
                Res.Add(f(mas[j][5]));
                Cpu.Add(t(mas[j][8]));
                Mem.Add(t(mas[j][9]));
                for (int k = i + 4; k < i + 9; k++)
                {
                    if (valuePairs.ContainsKey(mas[k][11]))
                        valuePairs[mas[k][11]] = valuePairs[mas[k][11]] + 1;
                    else valuePairs.Add(mas[k][11], 1);
                }
            }
            using (var sw = new StreamWriter("res.txt"))
            {
                sw.WriteLine("Mem total: " + string.Join(' ', Mem_total));
                sw.WriteLine("Mem free: " + string.Join(' ', Mem_free));
                sw.WriteLine("Mem used: " + string.Join(' ', Mem_used));
                sw.WriteLine("Mem buff/cache: " + string.Join(' ', Mem_buff_cache));
                sw.WriteLine("MSwap total: " + string.Join(' ', Swap_total));
                sw.WriteLine("Swap free: " + string.Join(' ', Swap_free));
                sw.WriteLine("Swap used: " + string.Join(' ', Swap_used));
                sw.WriteLine("Swap avail: " + string.Join(' ', Swap_avail));
                sw.WriteLine("VIRT: " + string.Join(' ', Virt));
                sw.WriteLine("RES: " + string.Join(' ', Res));
                sw.WriteLine("%CPU: " + string.Join(' ', Cpu));
                sw.WriteLine("%MEM: " + string.Join(' ', Mem));
                sw.WriteLine("top 5: " + string.Join(' ', valuePairs));
            }
        }
    }
}