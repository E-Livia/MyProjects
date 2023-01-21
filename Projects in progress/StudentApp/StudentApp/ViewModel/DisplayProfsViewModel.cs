using StudentApp.Commands;
using StudentApp.Model;
using StudentApp.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace StudentApp.ViewModel
{
    class DisplayProfsViewModel:BaseViewModel
    {
        private ObservableCollection<ProfModel> profs;
        private ProfLogic logicProf = new ProfLogic();
        dbPELEntities studentDb = new dbPELEntities();

        public ObservableCollection<ProfModel> ProfsCollection
        {
            get
            {
                return profs;
            }
            set
            {
                profs = value;
                OnPropertyChanged("ProfsCollection");
            }
        }

        public static ProfModel choosedProf;
        private ProfModel selectedProf;
        public ProfModel SelectedProf
        {
            get
            {
                return selectedProf;
            }
            set
            {
                selectedProf = value;
                if (selectedProf != null)
                {
                    CanExecuteDeleteCommand = true;
                    CanExecuteModifyCommand = true;
                    choosedProf = selectedProf;
                }
                OnPropertyChanged("SelectedProf");
            }
        }

        public bool CanExecuteDeleteCommand { get; set; }
        public bool CanExecuteModifyCommand { get; set; }

        public DisplayProfsViewModel()
        {
            ProfsCollection = new ObservableCollection<ProfModel>(logicProf.GetProfModels());
        }

        private ICommand modificaProfCommand;
        public ICommand ModificaProfCommand
        {
            get
            {
                if (modificaProfCommand == null)
                {
                    modificaProfCommand = new RelayCommands(ModificaProfMethod, param => CanExecuteModifyCommand);
                }
                return modificaProfCommand;
            }
        }
        private void ModificaProfMethod(object param)
        {
            UpdateProf startWindow = new UpdateProf();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = startWindow;
            startWindow.Show();
        }
        private ICommand stergeProfCommand;
        public ICommand StergeProfCommand
        {
            get
            {
                if (stergeProfCommand == null)
                {
                    stergeProfCommand = new RelayCommands(StergeProfMethod, param => CanExecuteDeleteCommand);
                }
                return stergeProfCommand;
            }
        }
        private void StergeProfMethod(object param)
        {
            studentDb.spProfessorDelete(selectedProf.Id);
            MessageBox.Show("Ai sters profesorul :" + SelectedProf.Nume + " " + SelectedProf.Prenume);
            DisplayProfs Window = new DisplayProfs();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = Window;
            Window.Show();

        }

        private ICommand backCommand;
        public ICommand BackCommand
        {
            get
            {
                if (backCommand == null)
                {
                    backCommand = new RelayCommands(BackMethod);
                }
                return backCommand;
            }
        }
        private void BackMethod(object param)
        {
            MainWindow startWindow = new MainWindow();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = startWindow;
            startWindow.Show();
        }

        private ICommand addProfCommand;
        public ICommand AddProfCommand
        {
            get
            {
                addProfCommand = new RelayCommands(AddProfMethod);

                return addProfCommand;
            }
        }
        private void AddProfMethod(object param)
        {
            AddProf addView = new AddProf();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = addView;
            addView.Show();
        }
    }
}
