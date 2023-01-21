using Hangman.Model;
using Hangman.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hangman.ViewModel
{
    class ChooseCategoryViewModel : ObservableObject
    {
        public ObservableCollection<bool> categories { get; set; } = new ObservableCollection<bool>();
        public static UserModel selectedUser = SignInViewModel.SignedInUser;

        public ChooseCategoryViewModel()
        {
            categories.Add(AllCategories);
            categories.Add(CarsCategory);
            categories.Add(MoviesCategory);
            categories.Add(CountriesCategory);
            categories.Add(FlowersCategory);
            categories.Add(AnimalsCategory);
        }

        public static Category chosenCategory;
        private bool _allCategories;
        public bool AllCategories
        {
            get
            {
                return _allCategories;
            }
            set
            {
                if(_allCategories==true)
                {
                    chosenCategory = Category.AllCategories;
                }
                OnPropertyChanged(ref _allCategories, value);
            }
        }

        private bool _carsCategory;
        public bool CarsCategory
        {
            get
            {
                return _carsCategory;
            }
            set
            {
                if(_carsCategory==true)
                {
                    chosenCategory = Category.Cars;
                }
                OnPropertyChanged(ref _carsCategory, value);
            }
        }

        private bool _moviesCategory;
        public bool MoviesCategory
        {
            get
            {
                return _moviesCategory;
            }
            set
            {
                if (_moviesCategory == true)
                {
                    chosenCategory = Category.Movies;
                }
                OnPropertyChanged(ref _moviesCategory, value);
            }
        }

        private bool _countriesCategory;
        public bool CountriesCategory
        {
            get
            {
                return _countriesCategory;
            }
            set
            {
                if (_countriesCategory == true)
                {
                    chosenCategory = Category.Countries;
                }
                OnPropertyChanged(ref _countriesCategory, value);
            }
        }

        private bool _flowersCategory;
        public bool FlowersCategory
        {
            get
            {
                return _flowersCategory;
            }
            set
            {
                if(_flowersCategory==true)
                {
                    chosenCategory = Category.Flowers;
                }
                OnPropertyChanged(ref _flowersCategory, value);
            }
        }

        private bool _animalsCategory;
        public bool AnimalsCategory
        {
            get
            {
                return _animalsCategory;
            }
            set
            {
                if(_animalsCategory==true)
                {
                    chosenCategory = Category.Animals;
                }
                OnPropertyChanged(ref _animalsCategory, value);
            }
        }
    }
}
