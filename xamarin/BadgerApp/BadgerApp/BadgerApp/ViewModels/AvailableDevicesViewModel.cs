using System;
using System.ComponentModel;
using Xamarin.Forms;

namespace BadgerApp.ViewModels
{
	class AvailableDevicesViewModel : ViewModelBase
    {
        DateTime dateTime = DateTime.Now;

        public AvailableDevicesViewModel()
        {
            Device.StartTimer(TimeSpan.FromMilliseconds(15), OnTimerTick);
        }

        bool OnTimerTick()
        {
            DateTime = DateTime.Now;
            return true;
        }

        public DateTime DateTime
        {
            private set
            {
                if ( dateTime != value )
                {
                    SetProperty(ref dateTime, value);
                }
            }

            get
            {
                return dateTime;
            }
        }
    }
}
