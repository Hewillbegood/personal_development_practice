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
using System.Collections.ObjectModel;

namespace ManagementSystemForSeedSales
{
	/// <summary>
	/// Receipt.xaml 的交互逻辑
	/// </summary>
	public partial class Receipt : Window
	{
            // <Common Functions>
		public Receipt()
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
                  this.sitesComboBoxCollection = new ComboBox[3] { this.comboBox, this.comboBox_Copy, this.comboBox_Copy1 };
                  DataTable DT = DBAccess.GetSitesDataTableNonUpdate(" ds.County", "");
                  this.comboBox.ItemsSource = DT.DefaultView;
                  this.comboBox.SelectedIndex = 0;
                  //
                  // breeds ComboBoxes.
                  //
                  this.breedsComboBoxCollection = new ComboBox[2] { this.comboBox1, this.comboBox1_Copy };
                  DataTable breedDT = DBAccess.GetBreedsDataTableNonUpdate(" db.Crop", "");
                  this.comboBox1.ItemsSource = breedDT.DefaultView;
                  this.comboBox1.SelectedIndex = 0;
                  //
                  // listView.
                  //
                  this.listView.ItemsSource = this.listViewSource;
                  //
                  // ticket index.
                  //
                  DataSuite ds = DBAccess.GetExtrasDataSuite();
                  DataRow dr1 = ds.DT.Rows[0];
                  string str = "票号: " + ((int)dr1["TicketsCountToday"]).ToString("D3");
                  this.label8_Copy3.Content = str;
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

            private string _customerName = "";
            public string CustomerName
            {
                  get { return this._customerName; }
                  set
                  {
                        if (value == "")
                        {
                              throw new ArgumentException("\"购种单位\"不可为空.");
                        }
                        else
                        {
                              this._customerName = value;
                        }
                  }
            }

            private ComboBox[] sitesComboBoxCollection;
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
                              this.sitesComboBoxCollection[i + 1].ItemsSource = DT.DefaultView;
                              this.sitesComboBoxCollection[i + 1].SelectedIndex = 0;
                        }
                  }
            }

            private double _quantity = 0.0D;
            public double Quantity
            {
                  get { return this._quantity; }
                  set
                  {
                        if (value <= 0)
                        {
                              throw new ArgumentException("\"数量\"必须大于 0.");
                        }
                        else
                        {
                              this._quantity = value;
                        }
                  }
            }

            private double _unitPrice = 0.0D;
            public double UnitPrice
            {
                  get { return this._unitPrice; }
                  set
                  {
                        if (value <= 0)
                        {
                              throw new ArgumentException("\"单价(￥)\"必须大于 0.");
                        }
                        else
                        {
                              this._unitPrice = value;
                        }
                  }
            }

            private void button1_Click(object sender, RoutedEventArgs e)
            {// Validation.GetHasError() first, then TextBox.Text validation.
                  if (this.listView.Items.Count >= 5)
                  {
                        MessageBox.Show("列表项数不能超过 5.", "添加项被阻止", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (Validation.GetHasError(this.textBox1))
                  {
                        MessageBox.Show("\"数量(斤)\"填写有误.", "添加项被阻止", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (this.textBox1.Text == "0")
                  {
                        MessageBox.Show("\"数量(斤)\"尚未填写.", "添加项被阻止", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (Validation.GetHasError(this.textBox1_Copy))
                  {
                        MessageBox.Show("\"单价(￥)\"填写有误.", "添加项被阻止", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (this.textBox1_Copy.Text == "0")
                  {
                        MessageBox.Show("\"单价(￥)\"尚未填写.", "添加项被阻止", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else
                  {
                        bool exists = false;
                        for (int i = 0; i < this.listViewSource.Count; i++)
                        {
                              if((string)((MainListItem)this.listViewSource[i]).DataSuite.DT.Rows[0]["Crop"]
                                    == (string)this.comboBox1.SelectedValue 
                                    && (string)((MainListItem)this.listViewSource[i]).DataSuite.DT.Rows[0]["Breed"]
                                    == (string)this.comboBox1_Copy.SelectedValue)
                              {
                                    exists = true;
                                    break;
                              }
                        }
                        if(exists)
                        {
                              MessageBox.Show("此品种已在列表中.", "添加项被阻止", MessageBoxButton.OK, MessageBoxImage.Error);
                        }
                        else
                        {// wait, repeat validation and Quantity vs. Stock.
                              string fieldsString = " db.Crop, db.Breed, db.Source, db.Rank, db.Pureness, db.Neatness, db.GerminationPercentage, db.Humidity, db.Stock";
                              string filterString = " WHERE db.Crop=\'" + this.comboBox1.SelectedValue + "\' AND db.Breed=\'"
                                    + this.comboBox1_Copy.SelectedValue + "\'";
                              DataSuite ds = DBAccess.GetBreedsDataSuiteUpdate(fieldsString, filterString);
                              if (ds.DT.Rows.Count <= 0)
                              {
                                    MessageBox.Show("可以看得出, 品种数据库里一项都没有.", "添加项被阻止", MessageBoxButton.OK,
                                          MessageBoxImage.Error);
                              }
                              else if ((double)ds.DT.Rows[0]["Stock"] < this.Quantity)
                              {
                                    MessageBox.Show("\"数量(斤)\"超出库存.", "添加项被阻止", MessageBoxButton.OK,
                                          MessageBoxImage.Error);
                              }
                              else
                              {
                                    MainListItem mli = new MainListItem(ds, this.Quantity, this.UnitPrice);
                                    this.listViewSource.Add(mli);
                                    this.textBlock.Text = "总额: ￥" + (this.total += mli.CashAmount).ToString("N2");
                                    //
                                    this._quantity = 0.0D;
                                    this._unitPrice = 0.0D;
                                    this.textBox1.Text = "0";
                                    this.textBox1_Copy.Text = "0";
                              }                         
                        }
                  }
            }

            private ComboBox[] breedsComboBoxCollection;
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
                              filterSB.Append(" WHERE db.Crop=\'" + this.comboBox1.SelectedValue + "\'");
                              fieldsSB.Append(" db." + this.comboBox1.SelectedValuePath);
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
                              this.breedsComboBoxCollection[i + 1].ItemsSource = DT.DefaultView;
                              this.breedsComboBoxCollection[i + 1].SelectedIndex = 0;
                        }
                  }
            }

            public class MainListItem
            {
                  public DataSuite DataSuite { get; set; }
                  public double Quantity { get; set; }
                  public double CashAmount { get; set; }
                  public double UnitPrice { get; set; }
                  public MainListItem(DataSuite inDS, double inQ, double inU)
                  {
                        this.DataSuite = inDS;
                        this.Quantity = inQ;
                        this.UnitPrice = inU;
                        this.CashAmount = UnitPrice * Quantity;
                  }
            }
            private ObservableCollection<MainListItem> listViewSource = new ObservableCollection<MainListItem>();

            private void button1_Copy_Click(object sender, RoutedEventArgs e)
            {
                  int index = this.listView.SelectedIndex;
                  if (index < 0)
                  {
                        MessageBox.Show("找不到选定项.", "移除失败", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else
                  {
                        this.textBlock.Text = "总额: ￥" 
                              + (this.total -= ((MainListItem)this.listView.SelectedItem).CashAmount).ToString("N2");
                        this.listViewSource.RemoveAt(index);
                  } 
            }

            private double total = 0;

            private void button1_Copy1_Click(object sender, RoutedEventArgs e)
            {
                  this._customerName = "";
                  this.textBox.Text = "";
                  this.comboBox.SelectedIndex = 0;
                  this.comboBox1.SelectedIndex = 0;
                  this.textBox1.Text = "0";
                  this.textBox1_Copy.Text = "0";
                  this._quantity = 0.0D;
                  this.listViewSource.Clear();
                  this.textBlock.Text = "总额: ￥0";
                  this.total = 0.0D;
                  this.textBox2.Text = "";
            }

            private PrintDialog printDialog = new PrintDialog();

            private void button1_Copy2_Click(object sender, RoutedEventArgs e)
            {
                  if(Validation.GetHasError(this.textBox))
                  {
                        MessageBox.Show("\"购种单位\"填写有误.", "无法继续", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (this.textBox.Text == "")
                  {
                        MessageBox.Show("\"购种单位\"尚未填写.", "无法继续", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (this.listViewSource.Count == 0)
                  {
                        MessageBox.Show("列表为空.", "无法继续", MessageBoxButton.OK, MessageBoxImage.Error);
                  }
                  else if (this.textBox2.Text == "" && MessageBox.Show("联系电话未填写, 确认继续?", "询问",
                        MessageBoxButton.YesNo, MessageBoxImage.Error) != MessageBoxResult.Yes)
                  {
                  }
                  else
                  {
                        // print. 
                        if (printDialog.ShowDialog() == true)
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
                                    fText = new FormattedText("销售凭证",
                                          System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                          new Typeface("Microsoft YaHei"), 20, Brushes.Black);
                                    currentLeftMargin = (printDialog.PrintableAreaWidth - fText.Width) / 2;
                                    dc.DrawText(fText, new Point(currentLeftMargin, currentTopMargin));
                                    //
                                    // serial of information.
                                    //
                                    currentTopMargin += fText.Height + 10;
                                    fText = new FormattedText("购种单位: " + this.CustomerName + "          地址: "
                                          + this.comboBox.SelectedValue + this.comboBox_Copy.SelectedValue
                                          + this.comboBox_Copy1.SelectedValue + "          日期和时间: " + DateTime.Now.ToString()
                                          + "          " + this.label8_Copy3.Content.ToString(),
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
                                          - (new FormattedText("作物品种产地等级纯度(%)净度(%)芽率(%)水分(%)单价数量(斤)金额",
                                          System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                          new Typeface("Microsoft YaHei"), 12, Brushes.Black)).Width) / 10;
                                    eachMargin -= 10;
                                    string[] propertyStrings = new string[11] {"作物", "品种", "产地", "等级", "纯度(%)", "净度(%)", "芽率(%)", 
                                          "水分(%)", "单价", "数量(斤)", "金额"};
                                    FormattedText[] propertyFTexts = new FormattedText[11];
                                    for (int i = 0; i < 11; i++)
                                    {
                                          propertyFTexts[i] = new FormattedText(propertyStrings[i],
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                    }
                                    double[] propertyLeftMargins = new double[11];
                                    propertyLeftMargins[0] = 55;
                                    for (int i = 1; i < 11; i++)
                                    {
							if (i == 1)
							{
								propertyLeftMargins[i] = propertyLeftMargins[i - 1] + eachMargin + 20;
							}
							else if (i == 2)
							{
								propertyLeftMargins[i] = propertyLeftMargins[i - 1] + eachMargin + 40;
							}
                                          else if (i == 9)
                                          {
                                                propertyLeftMargins[i] = propertyLeftMargins[i - 1] + eachMargin + 55;
                                          }
                                          else
                                          {
                                                propertyLeftMargins[i] = propertyLeftMargins[i - 1] + eachMargin + 33;
                                          }

                                    }
                                    for (int i = 0; i < 11; i++)
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
                                    string[] dtFields = new string[8] {"Crop", "Breed", "Source", "Rank", "Pureness", "Neatness",
                                          "GerminationPercentage", "Humidity"};
                                    foreach (MainListItem mli in this.listViewSource)
                                    {
                                          for (int i = 0; i < 8; i++)
                                          {
                                                propertyFTexts[i] = new FormattedText(mli.DataSuite.DT.Rows[0][dtFields[i]].ToString(),
                                                      System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                      new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          }
                                          propertyFTexts[8] = new FormattedText(
                                                mli.UnitPrice.ToString("C", System.Globalization.CultureInfo.CurrentCulture),
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[9] = new FormattedText(mli.Quantity.ToString(),
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          propertyFTexts[10] = new FormattedText(mli.CashAmount.ToString("C",
                                                System.Globalization.CultureInfo.CurrentCulture),
                                                System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                                new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                          for (int i = 0; i < 11; i++)
                                          {
                                                dc.DrawText(propertyFTexts[i], new Point(propertyLeftMargins[i], currentTopMargin));
                                          }
                                          currentTopMargin += fText.Height + 5;
                                    }
                                    //
                                    // bottom line.
                                    //
                                    currentTopMargin = 280;
                                    dc.DrawLine(new Pen(Brushes.Black, 1), new Point(10, currentTopMargin),
                                          new Point(this.printDialog.PrintableAreaWidth - 10, currentTopMargin));
                                    //
                                    // total.
                                    //
                                    fText = new FormattedText(this.textBlock.Text,
                                          System.Globalization.CultureInfo.CurrentCulture, FlowDirection.LeftToRight,
                                          new Typeface("Microsoft YaHei"), 12, Brushes.Black);
                                    currentLeftMargin = printDialog.PrintableAreaWidth - 10 - 25 - fText.Width;
                                    dc.DrawText(fText, new Point(currentLeftMargin, currentTopMargin));
                              }
                              this.printDialog.PrintVisual(dv, "A Printing task from MSFSS.");
                              //
                              // dbo.Extras.
                              //
                              DataSuite ds = DBAccess.GetExtrasDataSuite();
                              DataRow dr = ds.DT.Rows[0];
                              int newTicketsCount = (int)dr["TicketsCountToday"];
                              newTicketsCount++;
                              this.label8_Copy3.Content = "票号: " + newTicketsCount.ToString("D3");
                              dr["TicketsCountToday"] = newTicketsCount;
                              double newSalesAmount = (double)dr["SalesAmountToday"];
                              newSalesAmount += this.total;
                              dr["SalesAmountToday"] = newSalesAmount;
                              DBAccess.UpdateToDB(ds);
                              //
                              // dbo.SalesLog, dbo.Breeds.Stock.
                              //
                              foreach (MainListItem mli in this.listViewSource)
                              {
                                    DBAccess.InsertIntoSalesLog(this.CustomerName, mli, (string)this.comboBox.SelectedValue,
                                          (string)this.comboBox_Copy.SelectedValue, (string)this.comboBox_Copy1.SelectedValue,
                                          this.textBox2.Text);
                                    double newStock = (double)mli.DataSuite.DT.Rows[0]["Stock"] - mli.Quantity;
                                    mli.DataSuite.DT.Rows[0]["Stock"] = newStock;
                                    DBAccess.UpdateToDB(mli.DataSuite);
                              }
                        }
                  }
            }
	}
}