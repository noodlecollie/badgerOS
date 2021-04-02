using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;
using Rg.Plugins.Popup.Services;

namespace BadgerApp.Views
{
	[XamlCompilation(XamlCompilationOptions.Compile)]
	public partial class DeviceSettingsView : ContentPage
	{
		public DeviceSettingsView()
		{
			InitializeComponent();
		}

		private async void DeveloperSettings_Clicked(object sender, EventArgs e)
		{
			Views.DeveloperPopupView popup = new Views.DeveloperPopupView();
			await PopupNavigation.Instance.PushAsync(popup);
		}
	}
}