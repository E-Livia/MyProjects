using Hangman.Model;
using Hangman.Services;
using Hangman.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Threading;

namespace Hangman.ViewModel
{
    public class GameViewModel : ObservableObject
    {
        private Serialization actions = new Serialization();
        private ObservableCollection<Button> buttonsCollection = new ObservableCollection<Button>();

        #region FileCommandsRegion
        public ICommand NewGameCommand { get; }
        public ICommand OpenGameCommand { get; }
        public ICommand SaveGameCommand { get; }
        public ICommand StatisticsCommand { get; }
        public ICommand ExitCommand { get; }
        #endregion

        public ICommand ChangeCategoryCommand { get; }
        public ICommand LetterCommand { get; }
        public ICommand AboutCommand { get; }


        private DispatcherTimer dispatcherTimer = new DispatcherTimer();
        private int seconds = 60;
        private DateTime deadline;
        private Random random = new Random();
        private Words words;
        UserModel currentUser;
        SignInViewModel signInViewModel;
        public static UserModel selectedUser = SignInViewModel.SignedInUser;

        public GameViewModel()
        {
            currentUser = SignInViewModel.SignedInUser;
            words = new Words();
            words = actions.DeserializeWords("./../../Xml/Words.xml");
            signInViewModel = actions.DeserializeUsers("./../../Xml/User.xml");

            NewGameCommand = new RelayCommand(NewGame);
            OpenGameCommand = new RelayCommand(OpenGame);
            SaveGameCommand = new RelayCommand(SaveGame);
            StatisticsCommand = new RelayCommand(Stats);
            ExitCommand = new RelayCommand(BackToSignIn);
            ChangeCategoryCommand = new RelayCommand(ChangeCategory);
            LetterCommand = new RelayCommand(Letter);
            AboutCommand = new RelayCommand(About);

            CurrentMistakeImage = "/Images/mistakes0.jpg";

            switch (ChooseCategoryViewModel.chosenCategory)
            {
                case Category.AllCategories:
                    AllCategoryChecked = true;
                    _category = Category.AllCategories;
                    break;
                case Category.Cars:
                    CarsCategoryChecked = true;
                    _category = Category.Cars;
                    break;
                case Category.Movies:
                    MoviesCategoryChecked = true;
                    _category = Category.Movies;
                    break;
                case Category.Countries:
                    CountrieCategoryChecked = true;
                    _category = Category.Countries;
                    break;
                case Category.Flowers:
                    FlowersCategoryChecked = true;
                    _category = Category.Flowers;
                    break;
                case Category.Animals:
                    AnimalsCategoryChecked = true;
                    _category = Category.Animals;
                    break;
                default:
                    break;
            }
            PickedWordsCollection = PickWords(_category);
            WordIndex = 0;
            CurrentMistakeImage = "/Images/mistakes0.jpg";
            Level = 1;
            Word = Codification(_pickedWords[0]);
            dispatcherTimer.Tick += new EventHandler(TimerTick);
            StartTimer(Seconds);
        }
        public GameViewModel(int level, string word, Category categoryProperty, int mistakes, int wordIndex, ObservableCollection<string> pickedWordsCollection, int sec, string imagePath)
        {
            currentUser = SignInViewModel.SignedInUser;
            Level = level;
            Word = word;
            CategoryProperty = categoryProperty;
            switch (CategoryProperty)
            {
                case Category.AllCategories:
                    AllCategoryChecked = true;
                    break;
                case Category.Cars:
                    CarsCategoryChecked = true;
                    break;
                case Category.Movies:
                    MoviesCategoryChecked = true;
                    _category = Category.Movies;
                    break;
                case Category.Countries:
                    CountrieCategoryChecked = true;
                    _category = Category.Countries;
                    break;
                case Category.Flowers:
                    FlowersCategoryChecked = true;
                    _category = Category.Flowers;
                    break;
                case Category.Animals:
                    AnimalsCategoryChecked = true;
                    _category = Category.Animals;
                    break;
                default:
                    break;
            }
            Mistakes = mistakes;
            WordIndex = wordIndex;
            PickedWordsCollection = pickedWordsCollection;
            Seconds = sec;
            StartTimer(Seconds);
            CurrentMistakeImage = imagePath;
            signInViewModel = actions.DeserializeUsers("./../../Xml/User.xml");
            dispatcherTimer.Tick += new EventHandler(TimerTick);
            words = new Words();
            words = actions.DeserializeWords("./../../Xml/Words.xml");
        }

        #region AboutUser
        public string UserName
        {
            get
            {
                return currentUser.Name;
            }
        }
        public string UserImagePath
        {
            get
            {
                return currentUser.ImagePath;
            }
        }
        private int _level;
        public int Level
        {
            get
            {
                return _level;
            }
            set
            {
                OnPropertyChanged(ref _level, value);
            }
        }
        #endregion

        #region CategorySelection
        private Category _category;
        public Category CategoryProperty
        {
            get
            {
                return _category;
            }
            set
            {
                OnPropertyChanged(ref _category, value);
            }
        }

        private bool _allCategoryChecked;
        public bool AllCategoryChecked
        {
            get
            {
                return _allCategoryChecked;
            }
            set
            {
                OnPropertyChanged(ref _allCategoryChecked, value);
            }
        }

        private bool _carsCategoryChecked;
        public bool CarsCategoryChecked
        {
            get
            {
                return _carsCategoryChecked;
            }
            set
            {
                OnPropertyChanged(ref _carsCategoryChecked, value);
            }
        }

        private bool _moviesCategoryChecked;
        public bool MoviesCategoryChecked
        {
            get
            {
                return _moviesCategoryChecked;
            }
            set
            {
                OnPropertyChanged(ref _moviesCategoryChecked, value);
            }
        }

        private bool _countriesCategoryChecked;
        public bool CountrieCategoryChecked
        {
            get
            {
                return _countriesCategoryChecked;
            }
            set
            {
                OnPropertyChanged(ref _countriesCategoryChecked, value);
            }
        }

        private bool _flowersCategoryChecked;
        public bool FlowersCategoryChecked
        {
            get
            {
                return _flowersCategoryChecked;
            }
            set
            {
                OnPropertyChanged(ref _flowersCategoryChecked, value);
            }
        }

        private bool _animalsCategoryChecked;
        public bool AnimalsCategoryChecked
        {
            get
            {
                return _animalsCategoryChecked;
            }
            set
            {
                OnPropertyChanged(ref _animalsCategoryChecked, value);
            }
        }
        #endregion

        #region AboutWords
        private ObservableCollection<string> _pickedWords = new ObservableCollection<string>();
        public ObservableCollection<string> PickedWordsCollection
        {
            get
            {
                return _pickedWords;
            }
            set
            {
                OnPropertyChanged(ref _pickedWords, value);
            }
        }

        private int _wordIndex;
        public int WordIndex
        {
            get
            {
                return _wordIndex;
            }
            set
            {
                OnPropertyChanged(ref _wordIndex, value);
            }
        }

        //generate random word
        public ObservableCollection<string> PickWords(Category category)
        {
            int carsCount = words.Cars.Count;
            int moviesCount = words.Movies.Count;
            int countriesCount = words.Countries.Count;
            int flowersCount = words.Flowers.Count;
            int animalsCount = words.Animals.Count;
            switch (category)
            {
                case Category.AllCategories:
                    int count = 5;
                    for (int i = 0; i < 6; i++)
                    {
                        int categoryIndex = random.Next(count);
                        switch (categoryIndex)
                        {
                            case 0:
                                PickedWordsCollection.Add(words.Cars[random.Next(carsCount)]);
                                break;
                            case 1:
                                PickedWordsCollection.Add(words.Movies[random.Next(moviesCount)]);
                                break;
                            case 2:
                                PickedWordsCollection.Add(words.Countries[random.Next(countriesCount)]);
                                break;
                            case 3:
                                PickedWordsCollection.Add(words.Flowers[random.Next(flowersCount)]);
                                break;
                            case 4:
                                PickedWordsCollection.Add(words.Animals[random.Next(animalsCount)]);
                                break;
                        }
                    }
                    break;
                case Category.Cars:
                    for (int i = 0; i < 6; i++)
                    {
                        PickedWordsCollection.Add(words.Cars[random.Next(carsCount)]);
                    }
                    break;
                case Category.Movies:
                    for (int i = 0; i < 6; i++)
                    {
                        PickedWordsCollection.Add(words.Movies[random.Next(moviesCount)]);
                    }
                    break;
                case Category.Countries:
                    for (int i = 0; i < 6; i++)
                    {
                        PickedWordsCollection.Add(words.Countries[random.Next(countriesCount)]);
                    }
                    break;
                case Category.Flowers:
                    for (int i = 0; i < 6; i++)
                    {
                        PickedWordsCollection.Add(words.Flowers[random.Next(flowersCount)]);
                    }
                    break;
                case Category.Animals:
                    for (int i = 0; i < 6; i++)
                    {
                        PickedWordsCollection.Add(words.Animals[random.Next(animalsCount)]);
                    }
                    break;
                default:
                    break;
            }
            return PickedWordsCollection;
        }

        //word information
        private bool WordState(string wordToBeChanged)
        {
            if (wordToBeChanged.Contains("*"))
            {
                return false;
            }
            return true;
        }

        private string Codification(string word)
        {
            string codifiedWord = new Regex("\\S").Replace(word, "*");
            return codifiedWord;
        }

        private string _word;
        public string Word
        {
            get
            {
                return _word;
            }
            set
            {
                OnPropertyChanged(ref _word, value);
            }
        }
        #endregion

        private void NewGame(object o)
        {
            var newGame = new GameWindow();
            signInViewModel.SelectedUser = SignInViewModel.SignedInUser;
            App.Current.MainWindow.Close();
            App.Current.MainWindow = newGame;
            newGame.Show();
        }

        private void OpenGame(object o)
        {
            GameViewModel game = new GameViewModel(SignInViewModel.SignedInUser.GameProperty.Level, SignInViewModel.SignedInUser.GameProperty.Word, SignInViewModel.SignedInUser.GameProperty.CategoryProp, SignInViewModel.SignedInUser.GameProperty.Mistakes, SignInViewModel.SignedInUser.GameProperty.WordIndex, SignInViewModel.SignedInUser.GameProperty.WordsCollection, SignInViewModel.SignedInUser.GameProperty.Seconds, SignInViewModel.SignedInUser.GameProperty.ImagePath);
            GameWindow gameWindow = new GameWindow(game);
            signInViewModel.SelectedUser = SignInViewModel.SignedInUser;
            App.Current.MainWindow.Close();
            App.Current.MainWindow = gameWindow;
            gameWindow.Show();
        }

        public void SaveGame(object o)
        {
            Seconds = (deadline - DateTime.Now).Seconds;
            currentUser.GameProperty = new GameModel(Level, Word, CategoryProperty, Mistakes, WordIndex, PickedWordsCollection, Seconds, CurrentMistakeImage);
            foreach (var savedUser in signInViewModel.UsersList)
            {
                if (savedUser.Name == currentUser.Name)
                {
                    savedUser.GameProperty = currentUser.GameProperty;
                    savedUser.IsInGame = true;
                }
            }
            actions.SerializeUsers("./../../Xml/User.xml", signInViewModel);
            StopTimer();
            MessageBoxResult messageBoxResult = MessageBox.Show("Your game was saved successfully!", "Game Saved", MessageBoxButton.OK);
            if (messageBoxResult == MessageBoxResult.OK)
            {
                var signIn = new MainWindow();
                App.Current.MainWindow.Close();
                App.Current.MainWindow = signIn;
                signIn.Show();
            }

        }

        public void BackToSignIn(object o)
        {
            Seconds = (deadline - DateTime.Now).Seconds;
            StopTimer();
            MessageBoxResult messageBoxResult = MessageBox.Show("Do you want to save your game?", "Save Game", MessageBoxButton.YesNo);
            if (messageBoxResult == MessageBoxResult.Yes)
            {
                SaveGame(o);
            }
            else
            {
                var signIn = new MainWindow();
                App.Current.MainWindow.Close();
                App.Current.MainWindow = signIn;
                signIn.Show();
            }
        }

        private void ResetGame()
        {
            ResetButtons();
            Mistakes = 0;
            Level = 1;
            CurrentMistakeImage = "/Images/mistakes0.jpg";
            Seconds = 60;
            StartTimer(Seconds);
            PickedWordsCollection.Clear();
            WordIndex = 0;
            PickedWordsCollection = PickWords(CategoryProperty);
            Word = Codification(PickedWordsCollection[WordIndex]);
            AllCategoryChecked = false;
            CarsCategoryChecked = false;
            MoviesCategoryChecked = false;
            CountrieCategoryChecked = false;
            FlowersCategoryChecked = false;
            AnimalsCategoryChecked = false;
        }

        public void ChangeCategory(object o)
        {
            int secondsRemaining = (deadline - DateTime.Now).Seconds;
            StopTimer();
            MessageBoxResult messageBox = MessageBox.Show("If you change the category, you will lose your progress.",
                "Do you want to change the category?",
                MessageBoxButton.OKCancel);
            if (messageBox == MessageBoxResult.OK)
            {
                LooseGame(CategoryProperty);
                AllCategoryChecked = false;
                CarsCategoryChecked = false;
                MoviesCategoryChecked = false;
                CountrieCategoryChecked = false;
                FlowersCategoryChecked = false;
                AnimalsCategoryChecked = false;
                switch (o)
                {
                    case "All Categories":
                        CategoryProperty = Category.AllCategories;
                        AllCategoryChecked = true;
                        break;
                    case "Cars":
                        CategoryProperty = Category.Cars;
                        CarsCategoryChecked = true;
                        break;
                    case "Movies":
                        CategoryProperty = Category.Movies;
                        MoviesCategoryChecked = true;
                        break;
                    case "Countrie":
                        CategoryProperty = Category.Countries;
                        CountrieCategoryChecked = true;
                        break;
                    case "Flowers":
                        CategoryProperty = Category.Flowers;
                        FlowersCategoryChecked = true;
                        break;
                    case "Animals":
                        CategoryProperty = Category.Animals;
                        AnimalsCategoryChecked = true;
                        break;
                    default:
                        break;
                }
                ResetGame();
            }
            if (messageBox == MessageBoxResult.Cancel)
            {
                switch (CategoryProperty)
                {
                    case Category.AllCategories:
                        AllCategoryChecked = true;
                        break;
                    case Category.Cars:
                        CarsCategoryChecked = true;
                        break;
                    case Category.Movies:
                        MoviesCategoryChecked = true;
                        break;
                    case Category.Countries:
                        CountrieCategoryChecked = true;
                        break;
                    case Category.Flowers:
                        FlowersCategoryChecked = true;
                        break;
                    case Category.Animals:
                        AnimalsCategoryChecked = true;
                        break;
                    default:
                        break;
                }
                Seconds = secondsRemaining;
                StartTimer(Seconds);
            }
        }

        #region Letter
        private void ResetButtons()
        {
            foreach (Button b in buttonsCollection)
            {
                b.IsEnabled = true;
                b.Foreground = Brushes.Black;
            }
        }

        private void Reload()
        {
            WordIndex++;
            if (WordIndex < PickedWordsCollection.Count)
            {
                Seconds = 60;
                StartTimer(Seconds);
                Word = Codification(PickedWordsCollection[WordIndex]);
                CurrentMistakeImage = "/Images/mistakes0.jpg";
                Mistakes = 0;
                Level++;
            }
            else
            {
                StopTimer();
                WinGame(CategoryProperty);
                MessageBoxResult messageBoxResult = MessageBox.Show("You won! Do you want to start a new game?", "Win Game", MessageBoxButton.YesNo);
                if (messageBoxResult == MessageBoxResult.Yes)
                {
                    GameWindow newGame = new GameWindow();
                    signInViewModel.SelectedUser = currentUser;
                    App.Current.MainWindow.Close();
                    App.Current.MainWindow = newGame;
                    newGame.Show();
                }
                else
                {
                    var signIn = new MainWindow();
                    App.Current.MainWindow.Close();
                    App.Current.MainWindow = signIn;
                    signIn.Show();
                }
            }
            ResetButtons();
        }

        private void Letter(object o)
        {
            Button button = o as Button;
            buttonsCollection.Add(o as Button);
            (o as Button).IsEnabled = false;
            (o as Button).Foreground = Brushes.Red;
            char buttonContent = button.Content.ToString()[0];
            bool foundLetter = false;
            for (int i = 0; i < PickedWordsCollection[WordIndex].Length; ++i)
            {
                if (PickedWordsCollection[WordIndex][i] == buttonContent)
                {
                    StringBuilder sb = new StringBuilder(Word);
                    sb[i] = buttonContent;
                    Word = sb.ToString();
                    foundLetter = true;
                }
            }
            if (WordState(Word) == true)
            {
                Reload();
            }
            if (foundLetter == false)
            {
                _mistakes++;
                if (_mistakes <= 6)
                {
                    Mistakes = _mistakes;
                    string path = "/Images/";
                    string imageName = "mistakes" + _mistakes.ToString() + ".jpg";
                    CurrentMistakeImage = path + imageName;
                }
                if (_mistakes == 6)
                {
                    StopTimer();
                    MessageBoxResult messageBoxResult = MessageBox.Show("You lost! Do you want to start a new game?", "Loose Game", MessageBoxButton.YesNo);
                    if (messageBoxResult == MessageBoxResult.Yes)
                    {
                        var newGame = new GameWindow();
                        GameViewModel.selectedUser = currentUser;
                        App.Current.MainWindow.Close();
                        App.Current.MainWindow = newGame;
                        newGame.Show();
                    }
                    else
                    {
                        var signIn = new MainWindow();
                        App.Current.MainWindow.Close();
                        App.Current.MainWindow = signIn;
                        signIn.Show();
                    }
                    LooseGame(CategoryProperty);
                }
            }

        }
        #endregion

        #region Time
        public int Seconds
        {
            get
            {
                return seconds;
            }
            set
            {
                OnPropertyChanged(ref seconds, value);
            }
        }

        public string _timer;
        public string DispatcherTimer
        {
            get
            {
                if ((deadline - DateTime.Now).Seconds < 10)
                {
                    return (deadline - DateTime.Now).Minutes.ToString() + ":0" + (deadline - DateTime.Now).Seconds.ToString();
                }
                return (deadline - DateTime.Now).Minutes.ToString() + ":" + (deadline - DateTime.Now).Seconds.ToString();
            }
            set
            {
                OnPropertyChanged(ref _timer, value);
            }
        }

        private void StartTimer(int seconds)
        {
            deadline = DateTime.Now.AddSeconds(Seconds);
            dispatcherTimer.Start();
        }

        private void StopTimer()
        {
            dispatcherTimer.Stop();
            Seconds = (deadline - DateTime.Now).Seconds;
            deadline = DateTime.Now.AddSeconds(Seconds);
        }

        private void TimerTick(object sender, EventArgs e)
        {
            int secondsRemaining = (deadline - DateTime.Now).Seconds;
            OnPropertyChanged("DispatcherTimer");
            if (secondsRemaining == 0)
            {
                dispatcherTimer.Stop();
                dispatcherTimer.IsEnabled = false;
                Seconds = 60;
                MessageBoxResult messageBoxResult = MessageBox.Show("Time has expired! You lost! Do you want to start a new game?", "Loose Game", MessageBoxButton.YesNo);
                if (messageBoxResult == MessageBoxResult.Yes)
                {
                    var newGame = new GameWindow();
                    signInViewModel.SelectedUser = currentUser;
                    App.Current.MainWindow.Close();
                    App.Current.MainWindow = newGame;
                    newGame.Show();
                }
                else
                {
                    var signIn = new MainWindow();
                    App.Current.MainWindow.Close();
                    App.Current.MainWindow = signIn;
                    signIn.Show();
                }
                LooseGame(CategoryProperty);
            }
        }
        #endregion

        public void About(object o)
        {
            var aboutWindow = new AboutWindow();
            aboutWindow.Show();
        }

        #region MistakesRegion
        public ObservableCollection<string> MistakesImages { get; set; }
        private string _currentMistakeImage;
        public string CurrentMistakeImage
        {
            get
            {
                return _currentMistakeImage;
            }
            set
            {
                OnPropertyChanged(ref _currentMistakeImage, value);
            }
        }

        private int _mistakes = 0;
        public int Mistakes
        {
            get
            {
                return _mistakes;
            }
            set
            {
                OnPropertyChanged(ref _mistakes, value);
            }
        }
        #endregion

        #region Win and Loose
        private void WinGame(Category category)
        {
            switch (category)
            {
                case Category.AllCategories:
                    currentUser.Stats.WonGamesOnAllCategories += 1;
                    break;
                case Category.Cars:
                    currentUser.Stats.WonGamesOnCars += 1;
                    break;
                case Category.Movies:
                    currentUser.Stats.WonGamesOnMovies += 1;
                    break;
                case Category.Countries:
                    currentUser.Stats.WonGamesOnCountries += 1;
                    break;
                case Category.Flowers:
                    currentUser.Stats.WonGamesOnFlowers++;
                    break;
                case Category.Animals:
                    currentUser.Stats.WonGamesOnAnimals++;
                    break;
                default:
                    break;
            }
            currentUser.Stats.TotalWonGames += 1;
            foreach (var savedUser in signInViewModel.UsersList)
            {
                if (savedUser.Name == currentUser.Name)
                {
                    savedUser.Stats = currentUser.Stats;
                }
            }
            actions.SerializeUsers("./../../Xml/User.xml", signInViewModel);
        }

        private void LooseGame(Category category)
        {
            switch (category)
            {
                //case Category.AllCategories:
                //    currentUser.Stats.LostGamesOnAllCategories += 1;
                //    break;
                case Category.Cars:
                    currentUser.Stats.LostGamesOnCars += 1;
                    break;
                case Category.Movies:
                    currentUser.Stats.LostGamesOnMovies += 1;
                    break;
                case Category.Countries:
                    currentUser.Stats.LostGamesOnCountries += 1;
                    break;
                case Category.Flowers:
                    currentUser.Stats.LostGamesOnFlowers += 1;
                    break;
                case Category.Animals:
                    currentUser.Stats.LostGamesOnAnimals += 1;
                    break;
                default:
                    break;
            }
            //currentUser.Stats.TotalLostGames += 1;
            foreach (var savedUser in signInViewModel.UsersList)
            {
                if (savedUser.Name == currentUser.Name)
                {
                    savedUser.Stats = currentUser.Stats;
                }
            }
            actions.SerializeUsers("./../../Xml/User.xml", signInViewModel);
        }
        #endregion

        #region Stats
        private void Stats(object o)
        {
            int secondsRemaining = (deadline - DateTime.Now).Seconds;
            StopTimer();
            StatisticsWindow statsWindow = new StatisticsWindow();
            StatisticsViewModel statisticsViewModel = new StatisticsViewModel(currentUser);
            statsWindow.DataContext = statisticsViewModel;
            statsWindow.ShowDialog();
            StartTimer(secondsRemaining);
        }
        #endregion
    }
}