using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data;
using System.Data.OleDb;

namespace ManagementSystemForSeedSales
{
      public class DBAccess
      {
            public static DataTable GetSitesDataTableNonUpdate(string fieldsString, string filterString)
            {
                  OleDbDataAdapter SDA = new OleDbDataAdapter("SELECT DISTINCT" + fieldsString 
                        + " FROM dbo_Sites AS ds" + filterString + " ORDER BY" + fieldsString, new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  SDA.Fill(DT);
                  return DT;
            }

            public static DataTable GetBreedsDataTableNonUpdate(string fieldsString, string filterString)
            {
                  OleDbDataAdapter SDA = new OleDbDataAdapter("SELECT DISTINCT" + fieldsString 
                        + " FROM dbo_Breeds AS db" + filterString + " ORDER BY" + fieldsString, new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  SDA.Fill(DT);
                  return DT;
            }

            public static DataSuite GetExtrasDataSuite()
            {
                  OleDbDataAdapter sda = new OleDbDataAdapter("SELECT * FROM dbo_Extras", new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable dt = new DataTable();
                  sda.Fill(dt);
                  return new DataSuite(dt, sda);
            }

            public static DataSuite GetBreedsDataSuiteUpdate(string fieldsString, string filterString)
            {
                  OleDbDataAdapter SDA = new OleDbDataAdapter("SELECT DISTINCT db.Indx," + fieldsString
                        + " FROM dbo_Breeds AS db" + filterString + " ORDER BY" + fieldsString, new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  SDA.Fill(DT);
                  return new DataSuite(DT, SDA);
            }

            public static DataSuite GetAllBreedsDataSuiteUpdate()
            {
                  OleDbDataAdapter SDA = new OleDbDataAdapter("SELECT * FROM dbo_Breeds AS db ORDER BY db.Crop, db.Breed",
                        new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  SDA.Fill(DT);
                  return new DataSuite(DT, SDA);
            }

            public static DataSuite GetAllSitesDataSuiteUpdate()
            {
                  OleDbDataAdapter SDA = new OleDbDataAdapter(
                        "SELECT * FROM dbo_Sites AS ds ORDER BY ds.County, ds.Country, ds.Village",
                        new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  SDA.Fill(DT);
                  return new DataSuite(DT, SDA);
            }

            public static void InsertIntoSalesLog(string customerName, Receipt.MainListItem mli, string county, string country,
                  string village, string tele)
            {
                  OleDbConnection conn = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb");
                  conn.Open();
                  OleDbCommand cmd = conn.CreateCommand();
                  cmd.CommandType = CommandType.Text;
                  cmd.CommandText = "INSERT INTO dbo_SalesLog VALUES(\'" + customerName + "\', \'" + county + "\', \'"
                        + country + "\', \'" + village + "\', \'" + DateTime.Now.ToString() + "\', \'"
                        + mli.DataSuite.DT.Rows[0]["Crop"].ToString() + "\', \'" + mli.DataSuite.DT.Rows[0]["Breed"].ToString() 
                        + "\', " + mli.Quantity.ToString() + ", " + mli.CashAmount.ToString() + ", \'" + tele + "\')";
                  cmd.ExecuteNonQuery();
                  conn.Close();
            }

            public static DataTable GetSalesLogs(string filter)
            {
                  OleDbDataAdapter SDA = new OleDbDataAdapter("SELECT * FROM dbo_SalesLog AS dsl" + filter + " ORDER BY dsl.DateAndTime, dsl.Crop, dsl.Breed, dsl.County, dsl.Country, dsl.Village, dsl.CustomerName",
                        new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  SDA.Fill(DT);
                  return DT;
            }

            public static void UpdateToDB(DataSuite inSDS)
            {
                  OleDbCommandBuilder builder = new OleDbCommandBuilder(inSDS.SDA);
                  inSDS.SDA.Update(inSDS.DT);
                  builder.Dispose();
            }

            public static bool InsertIntoBreeds(string crop, string breed, string source, string rank, double pure, double neat,
                  double germ, double humi, double stock)
            {
                  // existance.
                  OleDbDataAdapter SDA = new OleDbDataAdapter("SELECT * FROM dbo_Breeds AS db WHERE db.Crop=\'" + crop
                        + "\' AND db.Breed=\'" + breed + "\'", new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  int influencedRows = SDA.Fill(DT);
                  if (influencedRows > 0)
                  {
                        return false;
                  }
                  //
                  // insert. indx first.
                  //
                  DataSuite extrasDS = DBAccess.GetExtrasDataSuite();
                  int breedsCount = (int)extrasDS.DT.Rows[0]["BreedsCount"];
                  OleDbConnection conn = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb");
                  conn.Open();
                  OleDbCommand cmd = conn.CreateCommand();
                  cmd.CommandType = CommandType.Text;
                  cmd.CommandText = "INSERT INTO dbo_Breeds VALUES(" + breedsCount.ToString() + ", \'" + crop + "\', \'"
                        + breed + "\', \'" + source + "\', \'" + rank + "\', " + pure.ToString() + ", " + neat.ToString() + ", "
                        + germ.ToString() + ", " + humi.ToString() + ", " + stock.ToString() + ")";
                  cmd.ExecuteNonQuery();
                  conn.Close();
                  breedsCount++;
                  extrasDS.DT.Rows[0]["BreedsCount"] = breedsCount;
                  DBAccess.UpdateToDB(extrasDS);
                  return true;
            }

            public static bool InsertIntoSites(string county, string country, string village)
            {
                  // existance.
                  OleDbDataAdapter SDA = new OleDbDataAdapter("SELECT * FROM dbo_Sites AS ds WHERE ds.County=\'" + county
                        + "\' AND ds.Country=\'" + country + "\' AND ds.Village=\'" + village + "\'", new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb"));
                  DataTable DT = new DataTable();
                  int influencedRows = SDA.Fill(DT);
                  if (influencedRows > 0)
                  {
                        return false;
                  }
                  //
                  // insert. indx first.
                  //
                  DataSuite extrasDS = DBAccess.GetExtrasDataSuite();
                  int sitesCount = (int)extrasDS.DT.Rows[0]["SitesCount"];
                  OleDbConnection conn = new OleDbConnection("Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:DataBase Password=B7204lb;Data Source=MSFSS.mdb");
                  conn.Open();
                  OleDbCommand cmd = conn.CreateCommand();
                  cmd.CommandType = CommandType.Text;
                  cmd.CommandText = "INSERT INTO dbo_Sites VALUES(" + sitesCount.ToString() + ", \'" + county + "\', \'"
                        + country + "\', \'" + village + "\')";
                  cmd.ExecuteNonQuery();
                  conn.Close();
                  sitesCount++;
                  extrasDS.DT.Rows[0]["SitesCount"] = sitesCount;
                  DBAccess.UpdateToDB(extrasDS);
                  return true;
            }
      }

      public class DataSuite
      {
            public DataTable DT { get; set; }
            public OleDbDataAdapter SDA { get; set; }
            public DataSuite(DataTable inDT, OleDbDataAdapter inSDA)
            {
                  this.DT = inDT;
                  this.SDA = inSDA;
            }
      }
}
