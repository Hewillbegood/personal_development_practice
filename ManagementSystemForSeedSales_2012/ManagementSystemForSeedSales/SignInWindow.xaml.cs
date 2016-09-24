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

namespace ManagementSystemForSeedSales
{
	/// <summary>
	/// MainWindow.xaml 的交互逻辑
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			this.InitializeComponent();

			// 在此点下面插入创建对象所需的代码。
                  FocusManager.SetFocusedElement(this, passwordBox);
		}

            private void button_Copy_Click(object sender, RoutedEventArgs e)
            {
                  Application.Current.Shutdown();
            }

            private void button_Click(object sender, RoutedEventArgs e)
            {
                  if (this.passwordBox.Password == "0123456789")
                  {
                        StartAnimation theStartAniWin = new StartAnimation();
                        theStartAniWin.Show();
                        this.Close();
                  }
                  else
                  {
                        MessageBox.Show("密码有误", "登陆失败", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
            }
	}
}