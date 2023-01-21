using Hangman.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Hangman.Model
{
    [Serializable]
    public class UserModel : ObservableObject
    {
        [XmlAttribute]
        private string name;

        [XmlAttribute]
        private string imagePath;

        [XmlAttribute]
        private GameModel game;

        [XmlAttribute]
        private StatisticsModel stats;

        [XmlAttribute]
        private bool isInGame;

        public UserModel() { }
        public UserModel(string name, string imagePath)
        {
            Name = name;
            ImagePath = imagePath;
            Stats = new StatisticsModel();
        }

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

        public string ImagePath
        {
            get
            {
                return imagePath;
            }
            set
            {
                OnPropertyChanged(ref imagePath, value);
            }
        }

        public GameModel GameProperty
        {
            get
            {
                return game;
            }
            set
            {
                OnPropertyChanged(ref game, value);
            }
        }

        public StatisticsModel Stats
        {
            get
            {
                return stats;
            }
            set
            {
                OnPropertyChanged(ref stats, value);
            }
        }

        public bool IsInGame
        {
            get
            {
                return isInGame;
            }
            set
            {
                OnPropertyChanged(ref isInGame, value);
            }
        }
    }
}
