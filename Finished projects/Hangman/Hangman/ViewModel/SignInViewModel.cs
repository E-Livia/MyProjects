using Hangman.Model;
using Hangman.Services;
using Hangman.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Xml.Serialization;

namespace Hangman.ViewModel
{
    [Serializable]
    public class SignInViewModel : ObservableObject
    {
        public ICommand NewUserCommand { get; }
        public ICommand DeleteUserCommand { get; }
        public ICommand PlayCommand { get; }
        public ICommand CancelCommand { get; }
        public GameModel Game { get; set; }

        public static UserModel SignedInUser;
        private Serialization actions = new Serialization();
        
        public SignInViewModel()
        {
            SelectedUser = null;
            NewUserCommand = new RelayCommand(NewUser);
            DeleteUserCommand = new RelayCommand(DeleteUser);
            PlayCommand = new RelayCommand(Play);
            CancelCommand = new RelayCommand(Cancel);
        }

        #region ListOfUsers
        [XmlArray]
        private ObservableCollection<UserModel> usersList;
        public ObservableCollection<UserModel> UsersList
        {
            get
            {
                return usersList;
            }
            set
            {
                OnPropertyChanged(ref usersList, value);
            }
        }
        #endregion

        #region SelectedUser
        private UserModel selectedUser;
        public UserModel SelectedUser
        {
            get
            {
                return selectedUser;
            }
            set
            {
                selectedUser = value;
                if (selectedUser != null)
                {
                    SignedInUser = selectedUser;
                }
                OnPropertyChanged(ref selectedUser, value);
            }
        }
        #endregion

        public void NewUser(object o)
        {
            var newUser = new NewUser();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = newUser;
            newUser.ShowDialog();
        }
        
        public void DeleteUser(object o)
        {
            int index = 0;
            if (selectedUser == null)
            {
                MessageBox.Show("No user selected!");
            }
            else
            {
                foreach (var user in UsersList)
                {
                    if (user.Name == selectedUser.Name)
                    {
                        UsersList.RemoveAt(index);
                        break;
                    }
                    ++index;
                }
            }
            SelectedUser = null;
            actions.SerializeUsers("./../../Xml/User.xml", this);
        }

        public void Play(object o)
        {
            if (selectedUser == null)
            {
                MessageBox.Show("No user selected!");
            }
            else
            {
                var gameWindow = new GameWindow();
                App.Current.MainWindow.Close();
                App.Current.MainWindow = gameWindow;
                gameWindow.ShowDialog();
            }
        }

        public void Cancel(object o)
        {
            System.Windows.Application.Current.Shutdown();
        }
    }
}
