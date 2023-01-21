using Hangman.Model;
using Hangman.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Hangman.View;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media.Imaging;

namespace Hangman.ViewModel
{
    class NewUserViewModel : ObservableObject
    {
        public ObservableCollection<string> ImagesList { get; set; }
        public ICommand NextCommand { get; }
        public ICommand PreviousCommand { get; }
        public ICommand SaveUserCommand { get; }
        public ICommand DiscardCommand { get; }

        private Serialization actions = new Serialization();
        private SignInViewModel signInViewModel;

        public int imageIndex = 0;
        private string _currentImage;
        public string CurrentImage
        {
            get
            {
                return _currentImage;
            }
            set
            {
                OnPropertyChanged(ref _currentImage, value);
            }
        }

        public NewUserViewModel()
        {
            signInViewModel = actions.DeserializeUsers("./../../Xml/User.xml");

            ImagesList = new ObservableCollection<string>();
            ImagesList.Add($"/Images/1.jpg");
            ImagesList.Add($"/Images/2.jpg");
            ImagesList.Add($"/Images/3.jpg");
            ImagesList.Add($"/Images/4.jpg");
            ImagesList.Add($"/Images/5.jpg");
            ImagesList.Add($"/Images/6.jpg");
            ImagesList.Add($"/Images/7.jpg");
            ImagesList.Add($"/Images/8.jpg");

            NextCommand = new RelayCommand(NextImage);
            PreviousCommand = new RelayCommand(PreviousImage);
            SaveUserCommand = new RelayCommand(SaveUser);
            DiscardCommand = new RelayCommand(Discard);

            CurrentImage = ImagesList[0];
        }

        public void NextImage(object o)
        {
            if (imageIndex < ImagesList.Count() - 1)
            {
                imageIndex++;
                CurrentImage = ImagesList[imageIndex];
            }
            else
            {
                MessageBox.Show("There are no more images");
            }
        }

        public void PreviousImage(object o)
        {
            if (imageIndex > 0)
            {
                imageIndex--;
                CurrentImage = ImagesList[imageIndex];
            }
            else
            {
                MessageBox.Show("There are no more images");
            }
        }

        private string nameTextBox;
        public string NameTextBox
        {
            get
            {
                return nameTextBox;
            }
            set
            {
                OnPropertyChanged(ref nameTextBox, value);
            }
        }
        public bool CanExecuteSaveUserCommand(object o)
        {
            if (String.IsNullOrEmpty(nameTextBox))
            {
                return false;
            }
            int index = 0;
            foreach (var user in signInViewModel.UsersList)
            {
                if (user.Name == nameTextBox)
                {
                    return false;
                }
                ++index;
            }
            return true;
        }

        private void SaveUser(object o)
        {
            signInViewModel.UsersList.Add(new UserModel(NameTextBox, CurrentImage));
            actions.SerializeUsers("./../../Xml/User.xml", signInViewModel);
            var signIn = new MainWindow();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = signIn;
            signIn.Show();
        }

        private void Discard(object o)
        {
            var signIn = new MainWindow();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = signIn;
            signIn.Show();
        }
    }
}
