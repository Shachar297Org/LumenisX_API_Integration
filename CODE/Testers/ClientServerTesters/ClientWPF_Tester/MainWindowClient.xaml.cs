using LumX_API_Provider;
using LumXCommon;
using LumXNetStdClientServerCommon;
using LumXNetStdGlobalTracingHelper;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Windows;

namespace ClientWPF_Tester
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindowClient : Window, INotifyPropertyChanged
    {
        #region INotifyPropertyChangeImplementation

        public event PropertyChangedEventHandler PropertyChanged;

        private void NotifyPropertyChanged(String propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion

        #region Public Properties

        private ObservableCollection<string> m_eventsNames;
        public ObservableCollection<string> EventsNames
        {
            get => m_eventsNames;
            set
            {
                m_eventsNames = value;
                NotifyPropertyChanged(nameof(EventsNames));
            }
        }

        private string m_notifications;
        public string Notifications
        {
            get => m_notifications;
            set
            {
                m_notifications = value;
                NotifyPropertyChanged(nameof(Notifications));
            }
        }


        private Visibility m_retrySelfActivationVisibility;
        public Visibility SelfActivationVisibility
        {
            get => m_retrySelfActivationVisibility;
            set
            {
                m_retrySelfActivationVisibility = value;
                NotifyPropertyChanged(nameof(SelfActivationVisibility));
            }
        }

        #endregion

        private readonly IncomingCommandCallbackDelegate m_callback;

        public MainWindowClient()
        {
            AppDomain.CurrentDomain.UnhandledException += (o, e) =>
            {
                string logMessage = e.ExceptionObject.ToString();
                GlobalTraces.TraceEvent(AvailableTraceSources.Application, TraceEventType.Critical, 19003, logMessage);
                GlobalTraces.TraceEvent(AvailableTraceSources.Errors, TraceEventType.Critical, 19003, logMessage);

                string message = ((Exception)e.ExceptionObject).Message;

                MessageBox.Show($"Following Unhandled Error Occurred:\n\n{message}\n\nPlease refer log file for details\nClick on OK button to terminate the application",
                    "CLIENT");

                Environment.Exit(1);
            };

            InitializeComponent();
            DataContext = this;

            SelfActivationVisibility = Visibility.Hidden;

            m_callback = CommandsFromServerCallback;

            Loaded += MainWindowClient_Loaded;
        }

        private void MainWindowClient_Loaded(object sender, RoutedEventArgs e)
        {
            if (!LumX.Initialize("LumXEventsDictionary.xml",
                StatusUpdateCallback,
                m_callback,
                "Version: Main 123, Secondary 456",
                "Good morning, LumenisX"))
            {
                WindowCustomerDetails win = new WindowCustomerDetails();
                bool? res = win.ShowDialog();
                if (res.HasValue && res.Value)
                {
                    LumX.ExecuteDeviceSelfActivation();
                }
                else
                    Close();
            }

            EventsNames = new ObservableCollection<string>(LumX.EventsNames);
        }

        private void StatusUpdateCallback(LumXStateUpdateSeverity updateSeverity, 
            LumXErrorCode lumXError, 
            string notification)
        {


        }

        private void BtnSendMessage_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                LumX.SendEvent(txtKey.Text, txtValue.Text);

                Notifications += $"Event sent:\t{txtKey.Text} {txtValue.Text}\n";
            }
            catch (Exception ex)
            {
                Notifications += $"Error:\t{ex.Message}\n";
            }
        }

        private void CommandsFromServerCallback(string methodName, params object[] methodParams)
        {
            string message = methodName + ":\t";
            if(methodParams != null && methodParams.Length > 0)
            {
                foreach(object obj in methodParams)
                {
                    string objStr = obj == null ? "NULL" : obj.ToString();
                    message += objStr + ";\t";
                }

                if (methodParams.Length == 2 && methodParams[1] != null &&
                    string.Compare(methodParams[1].ToString(),
                    "SelfActivationFailed") == 0)
                {
                    SelfActivationVisibility = Visibility.Visible;
                }
            }

            if (!string.IsNullOrEmpty(message))
            {
                Notifications += $"Server Update:\t{message}\n";
            }
        }
        private void BtnRetrySelfActivation_Click(object sender, RoutedEventArgs e)
        {
            SelfActivationVisibility = Visibility.Hidden;
            WindowCustomerDetails win = new WindowCustomerDetails();
            bool? res = win.ShowDialog();
            if (res.HasValue && res.Value)
            {
                LumX.ExecuteDeviceSelfActivation();
            }
        }
    }
}
