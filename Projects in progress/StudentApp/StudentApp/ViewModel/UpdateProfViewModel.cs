using StudentApp.Commands;
using StudentApp.Model;
using StudentApp.View;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace StudentApp.ViewModel
{
    class UpdateProfViewModel:BaseViewModel
    {
        dbPELEntities studentDb = new dbPELEntities();
        private string nume = DisplayProfsViewModel.choosedProf.Nume;
        public string NumeProperty
        {
            get
            {

                return nume;
            }
            set
            {
                nume = value;
                OnPropertyChanged("NumeProperty");
            }
        }
        private string prenume = DisplayProfsViewModel.choosedProf.Prenume;
        public string PrenumeProperty
        {
            get
            {

                return prenume;
            }
            set
            {
                prenume = value;
                OnPropertyChanged("PrenumeProperty");
            }
        }
        private string cnp = DisplayProfsViewModel.choosedProf.CNP;
        public string CnpProperty
        {
            get
            {
                return cnp;
            }
            set
            {
                cnp = (string)value;
                OnPropertyChanged("CnpProperty");
            }
        }

        private string telefon = DisplayProfsViewModel.choosedProf.Telefon;
        public string TelefonProperty
        {
            get
            {
                return telefon;
            }
            set
            {
                telefon = (string)value;
                OnPropertyChanged("TelefonProperty");
            }
        }

        private ICommand updateProfCommand;
        public ICommand UpdateProfCommand
        {
            get
            {
                if (updateProfCommand == null)
                {
                    updateProfCommand = new RelayCommands(UpdateProfMethod);
                }
                return updateProfCommand;
            }
        }
        private void UpdateProfMethod(object param)
        {
            studentDb.spProfessorUpdate(DisplayProfsViewModel.choosedProf.Id, prenume, nume, cnp, telefon, true);
            MessageBox.Show("Ai modificat un profesor!");
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
            DisplayStudents Window = new DisplayStudents();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = Window;
            Window.Show();
        }
    }
}
