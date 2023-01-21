using Hangman.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Hangman.Model
{
    public enum Category
    {
        AllCategories,
        Cars,
        Movies,
        Countries,
        Flowers,
        Animals
    }

    [Serializable]
    public class GameModel : ObservableObject
    {
        [XmlAttribute]
        private int _level = -0;
        [XmlAttribute]
        private string _word = "";
        [XmlAttribute]
        private Category _category;
        [XmlAttribute]
        private int _seconds;
        [XmlAttribute]
        private int _mistakes;
        [XmlAttribute]
        private int _wordIndex;
        [XmlAttribute]
        private ObservableCollection<string> _wordsCollection;
        [XmlAttribute]
        private string _imagePath;

        public GameModel(int level,string word,Category category, int mistakes, int wordIndex, ObservableCollection<string> wordsCollection, int seconds, string imagePath)
        {
            Level = level;
            Word = word;
            CategoryProp = category;
            Mistakes = mistakes;
            WordIndex = wordIndex;
            WordsCollection = wordsCollection;
            Seconds = seconds;
            ImagePath = imagePath;
        }

        public GameModel()
        {

        }

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

        public Category CategoryProp
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

        public int Seconds
        {
            get
            {
                return _seconds;
            }
            set
            {
                OnPropertyChanged(ref _seconds, value);
            }
        }

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

        public ObservableCollection<string>WordsCollection
        {
            get
            {
                return _wordsCollection;
            }
            set
            {
                OnPropertyChanged(ref _wordsCollection, value);
            }
        }

        public string ImagePath
        {
            get
            {
                return _imagePath;
            }
            set
            {
                OnPropertyChanged(ref _imagePath, value);
            }
        }
    }
}
