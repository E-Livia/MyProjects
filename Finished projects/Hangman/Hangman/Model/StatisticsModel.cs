using Hangman.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hangman.Model
{
    public class StatisticsModel : ObservableObject
    {
        private int _totalWonGames;
        private int _totalLostGames;
        private int _wonGamesOnAllCategories;
        private int _lostGamesOnAllCategories;
        private int _wonGamesOnCars;
        private int _lostGamesOnCars;
        private int _wonGamesOnMovies;
        private int _lostGamesOnMovies;
        private int _wonGamesOnCountries;
        private int _lostGamesOnCountries;
        private int _wonGamesOnFlowers;
        private int _lostGamesOnFlowers;
        private int _wonGamesOnAnimals;
        private int _lostGamesOnAnimals;

        public StatisticsModel()
        {

        }

        public int TotalWonGames
        {
            get
            {
                return _totalWonGames;
            }
            set
            {
                OnPropertyChanged(ref _totalWonGames, value);
            }
        }

        public int TotalLostGames
        {
            get
            {
                return _totalLostGames;
            }
            set
            {
                OnPropertyChanged(ref _totalLostGames, value);
            }
        }

        public int WonGamesOnAllCategories
        {
            get
            {
                return _wonGamesOnAllCategories;
            }
            set
            {
                OnPropertyChanged(ref _wonGamesOnAllCategories, value);
            }
        }

        public int LostGamesOnAllCategories
        {
            get
            {
                return _lostGamesOnAllCategories;
            }
            set
            {
                OnPropertyChanged(ref _lostGamesOnAllCategories, value);
            }
        }

        public int WonGamesOnCars
        {
            get
            {
                return _wonGamesOnCars;
            }
            set
            {
                OnPropertyChanged(ref _wonGamesOnCars, value);
            }
        }

        public int LostGamesOnCars
        {
            get
            {
                return _lostGamesOnCars;
            }
            set
            {
                OnPropertyChanged(ref _lostGamesOnCars, value);
            }
        }

        public int WonGamesOnMovies
        {
            get
            {
                return _wonGamesOnMovies;
            }
            set
            {
                OnPropertyChanged(ref _wonGamesOnMovies, value);
            }
        }

        public int LostGamesOnMovies
        {
            get
            {
                return _lostGamesOnMovies;
            }
            set
            {
                OnPropertyChanged(ref _lostGamesOnMovies, value);
            }
        }

        public int WonGamesOnCountries
        {
            get
            {
                return _wonGamesOnCountries;
            }
            set
            {
                OnPropertyChanged(ref _wonGamesOnCountries, value);
            }
        }

        public int LostGamesOnCountries
        {
            get
            {
                return _lostGamesOnCountries;
            }
            set
            {
                OnPropertyChanged(ref _lostGamesOnCountries, value);
            }
        }

        public int WonGamesOnFlowers
        {
            get
            {
                return _wonGamesOnFlowers;
            }
            set
            {
                OnPropertyChanged(ref _wonGamesOnFlowers, value);
            }
        }

        public int LostGamesOnFlowers
        {
            get
            {
                return _lostGamesOnFlowers;
            }
            set
            {
                OnPropertyChanged(ref _lostGamesOnFlowers, value);
            }
        }

        public int WonGamesOnAnimals
        {
            get
            {
                return _wonGamesOnAnimals;
            }
            set
            {
                OnPropertyChanged(ref _wonGamesOnAnimals, value);
            }
        }

        public int LostGamesOnAnimals
        {
            get
            {
                return _lostGamesOnAnimals;
            }
            set
            {
                OnPropertyChanged(ref _lostGamesOnAnimals, value);
            }
        }
    }
}
