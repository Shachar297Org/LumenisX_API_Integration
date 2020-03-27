using LumXNetFrameworkUtils;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;

namespace ClientWPF_Tester
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        public bool IsSimulator { get; private set; }

        private void Application_Startup(object sender, StartupEventArgs e)
        {
            IsSimulator = KeyboardMonitor.AreKeysDown(KeyboardMonitor.ModifierKeysEnum.Control | KeyboardMonitor.ModifierKeysEnum.Shift, "S");
        }
    }
}
