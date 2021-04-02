using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows.Input;
using System.Diagnostics;
using Xamarin.Forms;

namespace BadgerApp.ViewModels
{
	class AvailableDevicesViewModel : ViewModelBase
    {
        public AvailableDevicesViewModel()
        {
            SampleList = new ObservableCollection<string>();
        }

        public ObservableCollection<string> SampleList
        {
            get => m_SampleList;

            set
            {
                if ( value != m_SampleList )
                {
                    SetProperty(ref m_SampleList, value);
                }
            }
        }

        public bool IsEmpty
        {
            get => m_SampleList.Count < 1;
        }

        public ICommand AddItemCommand => new Command(() =>
        {
            m_SampleList.Add("New item " + m_SampleList.Count);
            OnPropertyChanged("SampleList");
            OnPropertyChanged("IsEmpty");
        });

        public ICommand TestBluetoothPermissions => new Command(() =>
        {
            Trace.WriteLine("Scanning on Bluetooth");
            var adapter = Plugin.BluetoothLE.CrossBleAdapter.Current;
            adapter.Scan();
        });

        private ObservableCollection<string> m_SampleList;
    }
}
