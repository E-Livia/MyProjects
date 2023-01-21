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
    public class SignUpViewModel : ObservableObject
    {
        HotelTransilvaniaEntities hotel = new HotelTransilvaniaEntities();
        public ICommand SignUpCommand { get; }
        public ICommand BackCommand { get; }

        public SignUpViewModel()
        {
            SignUpCommand = new RelayCommand(SignUp);
            BackCommand = new RelayCommand(Back);
        }

        #region prop
        private string name;
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                OnPropertyChanged(ref name, value);
            }
        }
        private int phoneNo;
        public int PhoneNo
        {
            get
            {
                return phoneNo;
            }
            set
            {
                OnPropertyChanged(ref phoneNo, value);
            }
        }
        private int emailAddress;
        public int EmailAddress
        {
            get
            {
                return emailAddress;
            }
            set
            {
                OnPropertyChanged(ref emailAddress, value);
            }
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
        #endregion

        private void SignUp(object o)
        {
            string password = (o as PasswordBox).Password;
            UserBLL user = new UserBLL();
            if (!user.SignUp(Name, PhoneNo, EmailAddress,  Username,  password))
            {
                MessageBox.Show("This email is taken!");
                EmailAddress = 0;
            }
            else
            {
                hotel.AddClient(Name, PhoneNo, EmailAddress, Username, password);
                //SignInViewModels.activeUser = query;
                HotelMainWindow hotelMainWindow = new HotelMainWindow();
                App.Current.MainWindow.Close();
                App.Current.MainWindow = hotelMainWindow;
                hotelMainWindow.Show();
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
