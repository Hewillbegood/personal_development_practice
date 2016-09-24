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
	/// BreedsDataBase.xaml 的交互逻辑
	/// </summary>
	public partial class BreedsDataBase : Window
	{
		public BreedsDataBase()
		{
			this.InitializeComponent();
			
			// 在此点之下插入创建对象所需的代码。
                  DispatcherTimer timer = new DispatcherTimer();
                  timer.Interval = TimeSpan.FromSeconds(1);
                  timer.Tick += TimerTick;
                  timer.Start();
                  //
                  // comboBoxes.
                  //
                  this.comboBox.ItemsSource = cropCollection;
                  this.comboBox.SelectedIndex = 0;
                  this.comboBox_Copy.ItemsSource = rankCollection;
                  this.comboBox_Copy.SelectedIndex = 0;
                  //
                  // this.listView.
                  //
                  this.listView.ItemsSource = ds.DT.DefaultView;
                  //
                  // next comboBoxes.
                  //
                  this.comboBox1.ItemsSource = cropCollection;
                  this.comboBox_Copy1.ItemsSource = rankCollection;
		}

            private DataSuite ds = DBAccess.GetAllBreedsDataSuiteUpdate();

            private string[] cropCollection = new string[3] { "大豆", "玉米", "水稻" };
            private string[] rankCollection = new string[2] { "原", "良" };

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

            private void button1_Click(object sender, RoutedEventArgs e)
            {
                  try
                  {
                        if (DBAccess.InsertIntoBreeds((string)this.comboBox.SelectedValue, (string)this.textBox.Text,
                        (string)this.textBox_Copy.Text, (string)this.comboBox_Copy.SelectedValue,
                        Convert.ToDouble(this.textBox_Copy1.Text), Convert.ToDouble(this.textBox_Copy2.Text),
                        Convert.ToDouble(this.textBox_Copy3.Text), Convert.ToDouble(this.textBox_Copy4.Text),
                        Convert.ToDouble(this.textBox_Copy6.Text)))
                        {
                              MessageBox.Show(this.comboBox.SelectedValue.ToString() + " " + this.textBox.Text + " 添加成功.",
                                    "添加成功.", MessageBoxButton.OK, MessageBoxImage.Asterisk);
                              this.comboBox.SelectedIndex = 0;
                              this.comboBox_Copy.SelectedIndex = 0;
                              this.textBox.Text = "";
                              this.textBox_Copy.Text = "";
                              this.textBox_Copy1.Text = "";
                              this.textBox_Copy2.Text = "";
                              this.textBox_Copy3.Text = "";
                              this.textBox_Copy4.Text = "";
                              this.textBox_Copy6.Text = "";
                              this.ds = DBAccess.GetAllBreedsDataSuiteUpdate();
                              this.listView.ItemsSource = ds.DT.DefaultView;
                        }
                        else
                        {
                              MessageBox.Show("该品种已存在.", "添加失败", MessageBoxButton.OK, MessageBoxImage.Error);
                        }
                  }
                  catch (Exception ex)
                  {
                        MessageBox.Show(ex.Message, "存在错误的填写", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
            }

            private void button2_Click(object sender, RoutedEventArgs e)
            {
                  try
                  {
                        DBAccess.UpdateToDB(this.ds);
                        MessageBox.Show("错误的填写已被忽略, 如果存在的话.", "提交成功", MessageBoxButton.OK,
                              MessageBoxImage.Asterisk);
                  }
                  catch (Exception exc)
                  {
                        MessageBox.Show(exc.Message, "存在错误的填写", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
            }
	}
}