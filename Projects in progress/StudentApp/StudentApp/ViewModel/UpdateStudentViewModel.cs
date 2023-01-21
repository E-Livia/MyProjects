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
    class UpdateStudentViewModel:BaseViewModel
    {
        dbPELEntities studentDb = new dbPELEntities();
        private string nume = DisplayStudentsViewModel.choosedStudent.Nume;
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
        private string prenume = DisplayStudentsViewModel.choosedStudent.Prenume;
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
        private int idGrupa = DisplayStudentsViewModel.choosedStudent.GrupaId;
        public int IdGrupaProperty
        {
            get
            {

                return idGrupa;
            }
            set
            {
                idGrupa = value;
                OnPropertyChanged("IdGrupaProperty");
            }
        }

        private string email = DisplayStudentsViewModel.choosedStudent.Email;
        public string EmailProperty
        {
            get
            {
                return email;
            }
            set
            {
                email = (string)value;
                OnPropertyChanged("EmailProperty");
            }
        }

        private string cnp = DisplayStudentsViewModel.choosedStudent.CNP;
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
        private ICommand updateStudentCommand;
        public ICommand UpdateStudentCommand
        {
            get
            {
                if (updateStudentCommand == null)
                {
                    updateStudentCommand = new RelayCommands(UpdateStudentMethod);
                }
                return updateStudentCommand;
            }
        }
        private void UpdateStudentMethod(object param)
        {
            studentDb.spStudentUpdate(DisplayStudentsViewModel.choosedStudent.Id, idGrupa, prenume, nume, cnp, email, true);
            MessageBox.Show("Ai modificat un student!");
            DisplayStudents Window = new DisplayStudents();
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
