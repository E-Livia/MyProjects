using HotelNou;
using HotelNou.Model;
using HotelNou.View;
using HotelNou.ViewModel;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace HotelNou.ViewModel
{
    public class MainWindowViewModel : ObservableObject
    {
        //public static bool stateUser = false;
        public ICommand SignInCommand { get; }
        public ICommand SignUpCommand { get; }

        public MainWindowViewModel()
        {
            SignInCommand = new RelayCommand(SignIn);
            SignUpCommand = new RelayCommand(SignUp);
        }

        public void SignIn(object o)
        {
            var admin = new SignInWindow();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = admin;
            admin.ShowDialog();
        }

        public void SignUp(object o)
        {
            var newUser = new SignUpWindow();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = newUser;
            newUser.ShowDialog();
        }
    }
}
