using System;
using System.Collections.Generic;
using System.Text;

namespace BadgerApp.ViewModels
{
	class AvailableDevicesViewModel
	{
		public string SampleText 
		{
			get
			{
				return m_SampleText;
			}

			set
			{
				m_SampleText = value;
			}
		}

		private string m_SampleText = "Testing";
	}
}
