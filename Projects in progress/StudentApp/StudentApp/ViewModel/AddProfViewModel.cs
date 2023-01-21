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
    class AddProfViewModel:BaseViewModel
    {
        dbPELEntities studentDb = new dbPELEntities();
        public static Professor currentProfessor = new Professor();

        private string nume;
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
        private string prenume;
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
        private string cnp;
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
        private string telefon;
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
            DisplayProfs Window = new DisplayProfs();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = Window;
            Window.Show();
        }

        private ICommand addProfCommand;
        public ICommand AddProfCommand
        {
            get
            {
                if (addProfCommand == null)
                {
                    addProfCommand = new RelayCommands(AdaugaProfMethod);
                }
                return addProfCommand;
            }
        }
        private void AdaugaProfMethod(object param)
        {
            studentDb.spProfessorInsert(prenume, nume, cnp, telefon, true);
            MessageBox.Show("Ai adaugat un profesor!");
            DisplayProfs Window = new DisplayProfs();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = Window;
            Window.Show();


        }
    }
}
