using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace BadgerApp.Views
{
	[XamlCompilation(XamlCompilationOptions.Compile)]
	public partial class AvailableDevicesView : ContentPage
	{
		public AvailableDevicesView()
		{
			InitializeComponent();
		}

		private void ListView_ItemTapped(object sender, ItemTappedEventArgs e)
		{
			Trace.WriteLine("Item was tapped: " + e.ItemIndex);
		}
	}
}