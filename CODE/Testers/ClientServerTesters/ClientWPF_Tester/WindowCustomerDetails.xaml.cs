using LumX_API_Provider;
using LumXCommon;
using LumXNetFrameworkUtils;
using LumXNetStdGeoHelper;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Windows;
using System.Windows.Input;

namespace ClientWPF_Tester
{
    /// <summary>
    /// Interaction logic for WindowCustomerDetails.xaml
    /// </summary>
    public partial class WindowCustomerDetails : Window, INotifyPropertyChanged
    {
        private ObservableCollection<string> m_regions;
        public ObservableCollection<string> Regions
        {
            get => m_regions;
            set
            {
                m_regions = value;
                NotifyPropertyChanged(nameof(Regions));
            }
        }

        private ObservableCollection<string> m_countries;
        public ObservableCollection<string> Countries
        {
            get => m_countries;
            set
            {
                m_countries = value;
                NotifyPropertyChanged(nameof(Countries));
            }
        }

        private Visibility m_stateVisibility;
        public Visibility StateVisibility
        {
            get => m_stateVisibility;
            set
            {
                m_stateVisibility = value;
                NotifyPropertyChanged(nameof(StateVisibility));
            }
        }

        private ObservableCollection<string> m_usaStates;
        public ObservableCollection<string> USAStates
        {
            get => m_usaStates;
            set
            {
                m_usaStates = value;
                NotifyPropertyChanged(nameof(USAStates));
            }
        }

        private string m_firstName;
        public string FirstName
        {
            get => m_firstName;
            set
            {
                m_firstName = value;
                NotifyPropertyChanged(nameof(FirstName));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.FirstName);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_lastName;
        public string LastName
        {
            get => m_lastName;
            set
            {
                m_lastName = value;
                NotifyPropertyChanged(nameof(LastName));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.LastName);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_phoneNumber;
        public string PhoneNumber
        {
            get => m_phoneNumber;
            set
            {
                m_phoneNumber = value;
                NotifyPropertyChanged(nameof(PhoneNumber));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.PhoneNumber);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_emailAddress;
        public string EmailAddress
        {
            get => m_emailAddress;
            set
            {
                m_emailAddress = value;
                NotifyPropertyChanged(nameof(EmailAddress));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.EmailAddress);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_region;
        public string Region
        {
            get => m_region;
            set
            {
                m_region = value;
                NotifyPropertyChanged(nameof(Region));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.AddressRegion);

                CommandManager.InvalidateRequerySuggested();

                if (!string.IsNullOrEmpty(m_region))
                    Countries = new ObservableCollection<string>(LumX.GeoHelper_GetCountries(m_region));
            }
        }

        private string m_addressCountry;
        public string AddressCountry
        {
            get => m_addressCountry;
            set
            {
                m_addressCountry = value;
                NotifyPropertyChanged(nameof(AddressCountry));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.AddressCountry);

                CommandManager.InvalidateRequerySuggested();

                if (string.Compare(m_addressCountry, GeoHelper.COUNTRY_USA) == 0)
                {
                    StateVisibility = Visibility.Visible;
                }
                else
                {
                    StateVisibility = Visibility.Hidden;
                    AddressState = string.Empty;
                }
            }
        }

        private string m_addressState;
        public string AddressState
        {
            get => m_addressState;
            set
            {
                m_addressState = value;
                NotifyPropertyChanged(nameof(AddressState));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.AddressState);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_addressCity;
        public string AddressCity
        {
            get => m_addressCity;
            set
            {
                m_addressCity = value;
                NotifyPropertyChanged(nameof(AddressCity));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.AddressCity);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_addressZip;
        public string AddressZip
        {
            get => m_addressZip;
            set
            {
                m_addressZip = value;
                NotifyPropertyChanged(nameof(AddressZip));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.AddressZip);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_addressStreet;
        public string AddressStreet
        {
            get => m_addressStreet;
            set
            {
                m_addressStreet = value;
                NotifyPropertyChanged(nameof(AddressStreet));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.AddressStreet);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_addressNumber;
        public string AddressNumber
        {
            get => m_addressNumber;
            set
            {
                m_addressNumber = value;
                NotifyPropertyChanged(nameof(AddressNumber));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.AddressNumber);

                CommandManager.InvalidateRequerySuggested();
            }
        }

        private string m_deviceType;
        public string DeviceType
        {
            get => m_deviceType;
            set
            {
                m_deviceType = value;
                NotifyPropertyChanged(nameof(DeviceType));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.DeviceType);
            }
        }

        private string m_serialNumber;
        public string SerialNumber
        {
            get => m_serialNumber;
            set
            {
                m_serialNumber = value;
                NotifyPropertyChanged(nameof(SerialNumber));
                LumX.SetDeviceSelfActivationPropertyValue(value, DeviceActivationPropertyEnum.DeviceSerialNumber);
            }
        }

        private ICommand m_activateCommand;
        public ICommand ActivateCommand
        {
            get => m_activateCommand;
            set
            {
                m_activateCommand = value;
                NotifyPropertyChanged(nameof(ActivateCommand));
            }
        }

        public WindowCustomerDetails()
        {
            InitializeComponent();

            DataContext = this;

            Regions = new ObservableCollection<string>(LumX.GeoHelper_GetRegions());

            USAStates = new ObservableCollection<string>(LumX.GeoHelper_GetStatesOfUSA());

            ActivateCommand = new RelayCommand(
                o1 => DialogResult = true, 
                o2 => 
                {
                    DeviceActivationPropertyEnum deviceActivationProperty = DeviceActivationPropertyEnum.AllPropertiesOK;
                    return LumX.IsSelfActivationDataValid(ref deviceActivationProperty);
                } );
        }

        #region INotifyPropertyChangeImplementation

        public event PropertyChangedEventHandler PropertyChanged;

        private void NotifyPropertyChanged(String propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion
    }
}
