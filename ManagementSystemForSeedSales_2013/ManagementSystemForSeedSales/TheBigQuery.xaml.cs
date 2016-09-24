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
using System.Data;

namespace ManagementSystemForSeedSales
{
	/// <summary>
	/// TheBigQuery.xaml 的交互逻辑
	/// </summary>
	public partial class TheBigQuery : Window
	{
		public TheBigQuery()
		{
			this.InitializeComponent();
			
			// 在此点之下插入创建对象所需的代码。
                  DispatcherTimer timer = new DispatcherTimer();
                  timer.Interval = TimeSpan.FromSeconds(1);
                  timer.Tick += TimerTick;
                  timer.Start();
                  //
                  // initialize sites ComboBoxes.
                  //
                  this.sitesComboBoxCollection = new ComboBox[3] { this.comboBox, this.comboBox1, this.comboBox2 };
                  DataTable DT = DBAccess.GetSitesDataTableNonUpdate(" ds.County", "");
                  DataRow dr = DT.NewRow();
                  dr["County"] = "不限";
                  DT.Rows.InsertAt(dr, 0);
                  this.comboBox.ItemsSource = DT.DefaultView;
                  this.comboBox.SelectedIndex = 0;
                  //
                  // breeds ComboBoxes.
                  //
                  this.breedsComboBoxCollection = new ComboBox[2] { this.comboBox3, this.comboBox4 };
                  DataTable breedDT = DBAccess.GetBreedsDataTableNonUpdate(" db.Crop", "");
                  DataRow breedDR = breedDT.NewRow();
                  breedDR["Crop"] = "不限";
                  breedDT.Rows.InsertAt(breedDR, 0);
                  this.comboBox3.ItemsSource = breedDT.DefaultView;
                  this.comboBox3.SelectedIndex = 0;
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

            private DateTime _beginDate = DateTime.Now.Date;
            private DateTime _endDate = DateTime.Now.Date.AddDays(1);

            public DateTime BeginDate
            {
                  get { return this._beginDate; }
                  set { this._beginDate = value; }
            }

            public DateTime EndDate
            {
                  get { return this._endDate; }
                  set { this._endDate = value; }
            }

            private ComboBox[] sitesComboBoxCollection;
            private ComboBox[] breedsComboBoxCollection;
            private void comboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
            {
                  ComboBox source = (ComboBox)e.Source;
                  int i = 0;
                  while (source != this.sitesComboBoxCollection[i])
                  {
                        i++;
                  }
                  // i indicates the source ComboBox now.
                  if (i < 2)
                  { // except the last, for the next.
                        DataRowView selected = (DataRowView)source.SelectedItem;
                        if (selected != null)
                        {
                              // string building process.
                              StringBuilder filterSB = new StringBuilder();
                              StringBuilder fieldsSB = new StringBuilder();
                              filterSB.Append(" WHERE ds.County=\'" + this.comboBox.SelectedValue + "\'");
                              fieldsSB.Append(" ds." + this.comboBox.SelectedValuePath);
                              for (int j = 1; j <= i; j++)
                              {
                                    filterSB.Append(" AND ds." + sitesComboBoxCollection[j].SelectedValuePath
                                          + "=\'" + this.sitesComboBoxCollection[j].SelectedValue + "\'");
                                    fieldsSB.Append(", ds." + this.sitesComboBoxCollection[j].SelectedValuePath);
                              }
                              fieldsSB.Append(", ds." + this.sitesComboBoxCollection[i + 1].SelectedValuePath);
                              //
                              // get DataSuite through built strings.
                              //
                              DataTable DT = DBAccess.GetSitesDataTableNonUpdate(fieldsSB.ToString(), filterSB.ToString());
                              DataRow dr = DT.NewRow();
                              dr[sitesComboBoxCollection[i + 1].SelectedValuePath] = "不限";
                              DT.Rows.InsertAt(dr, 0);
                              this.sitesComboBoxCollection[i + 1].ItemsSource = DT.DefaultView;
                              this.sitesComboBoxCollection[i + 1].SelectedIndex = 0;
                        }
                  }
            }
            private void breedsComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
            {
                  ComboBox source = (ComboBox)e.Source;
                  int i = 0;
                  while (source != this.breedsComboBoxCollection[i])
                  {
                        i++;
                  }
                  // i indicates the source ComboBox now.
                  if (i < 1)
                  { // except the last, for the next.
                        DataRowView selected = (DataRowView)source.SelectedItem;
                        if (selected != null)
                        {
                              // string building process.
                              StringBuilder filterSB = new StringBuilder();
                              StringBuilder fieldsSB = new StringBuilder();
                              filterSB.Append(" WHERE db.Crop=\'" + this.comboBox3.SelectedValue + "\'");
                              fieldsSB.Append(" db." + this.comboBox3.SelectedValuePath);
                              for (int j = 1; j <= i; j++)
                              {
                                    filterSB.Append(" AND db." + breedsComboBoxCollection[j].SelectedValuePath
                                          + "=\'" + this.breedsComboBoxCollection[j].SelectedValue + "\'");
                                    fieldsSB.Append(", db." + this.breedsComboBoxCollection[j].SelectedValuePath);
                              }
                              fieldsSB.Append(", db." + this.breedsComboBoxCollection[i + 1].SelectedValuePath);
                              //
                              // get DataSuite through built strings.
                              //
                              DataTable DT = DBAccess.GetBreedsDataTableNonUpdate(fieldsSB.ToString(), filterSB.ToString());
                              DataRow dr = DT.NewRow();
                              dr[breedsComboBoxCollection[i + 1].SelectedValuePath] = "不限";
                              DT.Rows.InsertAt(dr, 0);
                              this.breedsComboBoxCollection[i + 1].ItemsSource = DT.DefaultView;
                              this.breedsComboBoxCollection[i + 1].SelectedIndex = 0;
                        }
                  }
            }

            private DataTable listViewSource = null;
            private void button1_Click(object sender, RoutedEventArgs e)
            {
                  StringBuilder sb = new StringBuilder();
                  sb.Append(" WHERE dsl.DateAndTime >= #" + this.calendar.SelectedDate.ToString()
                        + "# AND dsl.DateAndTime < #" + this.calendar1.SelectedDate.ToString() + "#");
                  if ((string)this.comboBox.SelectedValue != "不限")
                  {
                        sb.Append(" AND dsl.County = \'" + this.comboBox.SelectedValue + "\'");
                  }
                  if ((string)this.comboBox1.SelectedValue != "不限")
                  {
                        sb.Append(" AND dsl.Country = \'" + this.comboBox1.SelectedValue + "\'");
                  }
                  if ((string)this.comboBox2.SelectedValue != "不限")
                  {
                        sb.Append(" AND dsl.Village = \'" + this.comboBox2.SelectedValue + "\'");
                  }
                  if ((string)this.comboBox3.SelectedValue != "不限")
                  {
                        sb.Append(" AND dsl.Crop = \'" + this.comboBox3.SelectedValue + "\'");
                  } 
                  if ((string)this.comboBox4.SelectedValue != "不限")
                  {
                        sb.Append(" AND dsl.Breed = \'" + this.comboBox4.SelectedValue + "\'");
                  }
                  this.listViewSource = DBAccess.GetSalesLogs(sb.ToString());
                  this.listView.ItemsSource = this.listViewSource.DefaultView;
                  double cashSum = 0;
                  double quantitySum = 0;
                  foreach (DataRow dr in this.listViewSource.Rows)
                  {
                        cashSum += (double)dr["Cash"];
                        quantitySum += (double)dr["Quantity"];
                  }
                  this.textBlock1.Text = "总金额: ￥" + cashSum.ToString("N2");
                  this.textBlock.Text = "总数量(斤): " + quantitySum.ToString();
            }

            private PrintDialog printDialog = new PrintDialog();
            private void button1_Copy_Click(object sender, RoutedEventArgs e)
            {
                  if (this.listViewSource == null || this.listViewSource.Rows.Count < 1)
                  {
                        MessageBox.Show("无可打印的项.", "错误", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (this.printDialog.ShowDialog() == true)
                  {
                        {
                              DrawingVisual dv = new DrawingVisual();
                              using (DrawingContext dc = dv.RenderOpen())
                              {
                                    // first heading.
                                    FormattedText fText = new FormattedText("佳木斯市东风区久龙种业经销处",
                                          System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                          new Typeface("Microsoft YaHei"), 15, Brushes.Black);
                                    double currentLeftMargin = (printDialog.PrintableAreaWidth - fText.Width) / 2;
                                    double currentTopMargin = 60;
                                    dc.DrawText(fText, new Point(currentLeftMargin, currentTopMargin));
                                    //
                                    // second heading.
                                    //
                                    currentTopMargin += fText.Height;
                                    fText = new FormattedText("销售记录",
                                          System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                          new Typeface("Microsoft YaHei"), 20, Brushes.Black);
                                    currentLeftMargin = (printDialog.PrintableAreaWidth - fText.Width) / 2;
                                    dc.DrawText(fText, new Point(currentLeftMargin, currentTopMargin));
                                    //
                                    // serial of information.
                                    //
                                    currentTopMargin += fText.Height + 10;
                                    fText = new FormattedText(this.textBlock.Text + "          " + this.textBlock1.Text
                                          + "          查询时间: " + DateTime.Now.ToString(),
                                          System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                          new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                    currentLeftMargin = (printDialog.PrintableAreaWidth - fText.Width) / 2;
                                    dc.DrawText(fText, new Point(currentLeftMargin, currentTopMargin));
                                    //
                                    // some line.
                                    //
                                    currentTopMargin += fText.Height;
                                    dc.DrawLine(new Pen(Brushes.Black, 1), new Point(currentLeftMargin - 30, currentTopMargin),
                                          new Point(this.printDialog.PrintableAreaWidth - currentLeftMargin + 30, currentTopMargin));
                                    //
                                    // properties series.
                                    //
                                    currentTopMargin += 10;
                                    double eachMargin = (printDialog.PrintableAreaWidth - 20 - 20
                                          - (new FormattedText("购种单位联系电话地址日期和时间作物品种数量(斤)金额",
                                          System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                          new Typeface("Microsoft YaHei"), 12, Brushes.Black)).Width) / 10;
                                    eachMargin -= 10;
                                    string[] propertyStrings = new string[8] {"购种单位", "联系电话", "地址", "日期和时间", "作物", "品种", 
                                          "数量(斤)", "金额"};
                                    FormattedText[] propertyFTexts = new FormattedText[8];
                                    for (int i = 0; i < 8; i++)
                                    {
                                          propertyFTexts[i] = new FormattedText(propertyStrings[i],
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                    }
                                    double[] propertyLeftMargins = new double[8];
                                    propertyLeftMargins[0] = 35;
                                    for (int i = 1; i < 8; i++)
                                    {
							if (i == 1)
							{
								propertyLeftMargins[i] = propertyLeftMargins[i - 1] + propertyFTexts[i - 1].Width
									+ eachMargin + 50;
							}
                                          else if (i == 3)
                                          {
                                                propertyLeftMargins[i] = propertyLeftMargins[i - 1] + propertyFTexts[i - 1].Width
                                                      + eachMargin + 90;
                                          }
                                          else if (i == 4)
                                          {
                                                propertyLeftMargins[i] = propertyLeftMargins[i - 1] + propertyFTexts[i - 1].Width
                                                      + eachMargin + 30;
                                          }
                                          else if (i == 5 || i == 7)
                                          {
                                                propertyLeftMargins[i] = propertyLeftMargins[i - 1] + propertyFTexts[i - 1].Width
                                                      + eachMargin - 20 ;
                                          }
							else if (i == 6)
							{
								propertyLeftMargins[i] = propertyLeftMargins[i - 1] + propertyFTexts[i - 1].Width
									+ eachMargin + 20;
							}
                                          else
                                          {
                                                propertyLeftMargins[i] = propertyLeftMargins[i - 1] + propertyFTexts[i - 1].Width
                                                      + eachMargin;
                                          }
                                    }
                                    for (int i = 0; i < 8; i++)
                                    {
                                          dc.DrawText(propertyFTexts[i], new Point(propertyLeftMargins[i], currentTopMargin));
                                    }
                                    //
                                    // another line.
                                    //
                                    currentTopMargin += fText.Height;
                                    dc.DrawLine(new Pen(Brushes.Black, 1), new Point(10, currentTopMargin),
                                          new Point(this.printDialog.PrintableAreaWidth - 10, currentTopMargin));
                                    //
                                    // main contents.
                                    //
                                    currentTopMargin += 10;
                                    foreach(DataRow dr in this.listViewSource.Rows)
                                    {
                                          propertyFTexts[0] = new FormattedText((string)dr["CustomerName"],
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[1] = new FormattedText((string)dr["Telephone"],
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[2] = new FormattedText((string)dr["County"] + (string)dr["Country"]
                                                + (string)dr["Village"], System.Globalization.CultureInfo.CurrentCulture,
                                                FlowDirection.LeftToRight, new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[3] = new FormattedText(((DateTime)dr["DateAndTime"]).ToString(),
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[4] = new FormattedText((string)dr["Crop"],
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[5] = new FormattedText((string)dr["Breed"],
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[6] = new FormattedText(((double)dr["Quantity"]).ToString(),
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[7] = new FormattedText(((double)dr["Cash"]).ToString("C"),
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          for (int i = 0; i < 8; i++)
                                          {
                                                dc.DrawText(propertyFTexts[i], new Point(propertyLeftMargins[i], currentTopMargin));
                                          }
                                          currentTopMargin += fText.Height + 2;
                                    }
                              }
                              this.printDialog.PrintVisual(dv, "A Printing task from MSFSS.");
                        }
                  }
            }
	}
}