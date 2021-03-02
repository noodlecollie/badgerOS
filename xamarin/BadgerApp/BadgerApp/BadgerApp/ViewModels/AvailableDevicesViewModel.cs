using System;
using System.Collections.Generic;

namespace BadgerApp.ViewModels
{
	class AvailableDevicesViewModel : ViewModelBase
    {
        public AvailableDevicesViewModel()
        {
            SampleList = new List<string>();
            SampleList.Add("Butts");
            SampleList.Add("More Butts");
        }

        public List<string> SampleList
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

        private List<string> m_SampleList;
    }
}
