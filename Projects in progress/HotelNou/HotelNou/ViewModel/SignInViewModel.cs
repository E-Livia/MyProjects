using HotelNou.Model;
using HotelNou.Model.BusinessLogicLayer;
using HotelNou.View;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace HotelNou.ViewModel
{
    public class SignInViewModel : ObservableObject
    {
        HotelTransilvaniaEntities hotelTransilvania = new HotelTransilvaniaEntities();
        UserBLL user = new UserBLL();
        public static Clienti activeUser = new Clienti();
        public static Angajati activeEmployee = new Angajati();

        public ICommand SignInCommand { get; }
        public ICommand BackCommand { get; }

        public SignInViewModel()
        {
            SignInCommand = new RelayCommand(SignIn);
            BackCommand = new RelayCommand(Back);
        }

        private string username;
        public string Username
        {
            get
            {
                return username;
            }
            set
            {
                OnPropertyChanged(ref username, value);
            }
        }

        private void SignIn(object o)
        {
            bool administrator = false;
            string password = (o as PasswordBox).Password;
            if (Username == "administrator" && password == "parola")
            {
                //MessageBox.Show("V-ati logat ca administrator!");
                administrator = true;
            }
            if (Username == null || String.IsNullOrEmpty(password))
            {
                MessageBox.Show("Toate campurile sunt obligatorii!");
            }
            else
            {
                if (administrator == false)
                {
                    if (!user.SignIn(username, password))
                    {
                        MessageBox.Show("username sau parola gresite!");
                        username = "";
                        (o as PasswordBox).Password = "";
                    }
                    else
                    {
                        var query = (from user in hotelTransilvania.Clientis
                                     where user.username.Equals(username)
                                     select user).First();
                        activeUser = query;
                        //StartWindowViewModels.stateUser = true;
                        HotelMainWindow hotelMainWindow = new HotelMainWindow();
                        App.Current.MainWindow.Close();
                        App.Current.MainWindow = hotelMainWindow;
                        hotelMainWindow.Show();
                    }
                }
                if (administrator == true)
                {
                    AdministrateWindow admin = new AdministrateWindow();
                    App.Current.MainWindow.Close();
                    App.Current.MainWindow = admin;
                    admin.Show();
                }
            }
        }

        private void Back(object o)
        {
            MainWindow mainWindow = new MainWindow();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = mainWindow;
            mainWindow.Show();
        }
    }
}
