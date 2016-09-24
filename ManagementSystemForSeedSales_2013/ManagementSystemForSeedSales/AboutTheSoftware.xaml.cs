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
using System.Windows.Media.Animation;
using System.Windows.Threading;
using System.Collections;

namespace ManagementSystemForSeedSales
{
	/// <summary>
	/// AboutTheSoftware.xaml 的交互逻辑
	/// </summary>
	public partial class AboutTheSoftware : Window
	{
            // <Common Functions> 
		public AboutTheSoftware()
		{
			this.InitializeComponent();
			
			// 在此点之下插入创建对象所需的代码。
                  DispatcherTimer timer = new DispatcherTimer();
                  timer.Interval = TimeSpan.FromSeconds(1);
                  timer.Tick += TimerTick;
                  timer.Start();
		}

            private void TimerTick(object sender, EventArgs e)
            {
                  this.label5.Content = DateTime.Now.ToString();
            }

            private void Window_Loaded(object sender, RoutedEventArgs e)
            {
                  DoubleAnimation doubleAnimation = new DoubleAnimation();
                  doubleAnimation.To = 0.60;
                  doubleAnimation.BeginTime = TimeSpan.FromSeconds(1);
                  doubleAnimation.Duration = TimeSpan.FromSeconds(2);
                  this.label5.BeginAnimation(Label.OpacityProperty, doubleAnimation);
            }

            private void MainButtonsMouseEnter(object sender, RoutedEventArgs e)
            {
                  Label correspondingLabel = null;
                  Button convertedSender = (Button)sender;
                  if (convertedSender == this.button)
                  {
                        correspondingLabel = this.label1;
                  }
                  else if (convertedSender == this.button_Copy)
                  {
                        correspondingLabel = this.label1_Copy;
                  }
                  else if (convertedSender == this.button_Copy1)
                  {
                        correspondingLabel = this.label1_Copy1;
                  }
                  else if (convertedSender == this.button_Copy2)
                  {
                        correspondingLabel = this.label1_Copy2;
                  }
                  else if (convertedSender == this.button_Copy3)
                  {
                        correspondingLabel = this.label1_Copy3;
                  }
                  else if (convertedSender == this.button_Copy4)
                  {
                        correspondingLabel = this.label1_Copy4;
                  }
                  // begin a DoubleAnimation.
                  DoubleAnimation doubleAnimation = new DoubleAnimation();
                  doubleAnimation.To = 200;
                  doubleAnimation.Duration = TimeSpan.FromSeconds(0.5);
                  correspondingLabel.BeginAnimation(Button.WidthProperty, doubleAnimation);
            }

            private void MainButtonsMouseLeave(object sender, RoutedEventArgs e)
            {
                  Label correspondingLabel = null;
                  Button convertedSender = (Button)sender;
                  if (convertedSender == this.button)
                  {
                        correspondingLabel = this.label1;
                  }
                  else if (convertedSender == this.button_Copy)
                  {
                        correspondingLabel = this.label1_Copy;
                  }
                  else if (convertedSender == this.button_Copy1)
                  {
                        correspondingLabel = this.label1_Copy1;
                  }
                  else if (convertedSender == this.button_Copy2)
                  {
                        correspondingLabel = this.label1_Copy2;
                  }
                  else if (convertedSender == this.button_Copy3)
                  {
                        correspondingLabel = this.label1_Copy3;
                  }
                  else if (convertedSender == this.button_Copy4)
                  {
                        correspondingLabel = this.label1_Copy4;
                  }
                  // begin a DoubleAnimation.
                  DoubleAnimation doubleAnimation = new DoubleAnimation();
                  doubleAnimation.Duration = TimeSpan.FromSeconds(0.5);
                  correspondingLabel.BeginAnimation(Button.WidthProperty, doubleAnimation);
            }

            private void button_Copy4_Click(object sender, RoutedEventArgs e)
            {
                  SitesDataBase sdb = new SitesDataBase();
                  sdb.Show();
                  this.Close();
            }

            private void button_Copy3_Click(object sender, RoutedEventArgs e)
            {
                  BreedsDataBase bdb = new BreedsDataBase(); bdb.Show(); this.Close();
            }

            private void button_Copy2_Click(object sender, RoutedEventArgs e)
            {
                  Application.Current.Shutdown();
            }

            private void button_Copy1_Click(object sender, RoutedEventArgs e)
            {
                  AboutTheSoftware theAboutWin = new AboutTheSoftware();
                  theAboutWin.Show();
                  this.Close();
            }

            private void button_Copy_Click(object sender, RoutedEventArgs e)
            {
                  this.WindowState = WindowState.Minimized;
            }

            private void button_Click(object sender, RoutedEventArgs e)
            {
                  Receipt theReceiptWin = new Receipt();
                  theReceiptWin.Show();
                  this.Close();
            }

            private void Window_KeyDown(object sender, KeyEventArgs e)
            {
                  if (e.Key == Key.T && e.KeyboardDevice.IsKeyDown(Key.LeftShift) && e.KeyboardDevice.IsKeyDown(Key.RightCtrl))
                  {
                        Today today = new Today();
                        today.Show();
                        this.Close();
                  }
                  if (e.Key == Key.Q && e.KeyboardDevice.IsKeyDown(Key.LeftShift) && e.KeyboardDevice.IsKeyDown(Key.RightCtrl))
                  {
                        TheBigQuery tbq = new TheBigQuery();
                        tbq.Show();
                        this.Close();
                  }
            }
            // </Common Functions>
	}
}