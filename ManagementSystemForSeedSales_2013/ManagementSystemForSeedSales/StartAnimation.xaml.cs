using System;
using System.Collections.Generic;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Data;

namespace ManagementSystemForSeedSales
{
	/// <summary>
	/// StartAnimation.xaml 的交互逻辑
	/// </summary>
	public partial class StartAnimation : Window
	{
		public StartAnimation()
		{
			this.InitializeComponent();
			
			// 在此点之下插入创建对象所需的代码。
                  DataSuite ds = DBAccess.GetExtrasDataSuite();
                  DataRow dr = ds.DT.Rows[0];
                  if (DateTime.Now.Date != ((DateTime)ds.DT.Rows[0]["TheDateTime"]).Date)
                  {
                        dr["TheDateTime"] = DateTime.Now;
                        dr["SalesAmountToday"] = 0.0D;
                        dr["TicketsCountToday"] = 0;
                        DBAccess.UpdateToDB(ds);
                  }
		}

            private void Window_Loaded(object sender, RoutedEventArgs e)
            {
                  this.cornerTitleAnimation.Completed += CornerTitleAniCompleted;
            }

            private void CornerTitleAniCompleted(object sender, EventArgs e)
            {
                  AboutTheSoftware theAboutWin = new AboutTheSoftware();
                  theAboutWin.Show();
                  this.Close();
            }
	}
}