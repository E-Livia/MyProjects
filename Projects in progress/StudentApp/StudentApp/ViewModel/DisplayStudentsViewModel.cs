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
    class DisplayStudentsViewModel : BaseViewModel
    {
        private ObservableCollection<StudentModel> students;
        private StudentLogic logicStudent = new StudentLogic();
        dbPELEntities studentDb = new dbPELEntities();

        public ObservableCollection<StudentModel> StudentsCollection
        {
            get
            {
                return students;
            }
            set
            {
                students = value;
                OnPropertyChanged("StudentsCollection");
            }
        }

        public static StudentModel choosedStudent;
        private StudentModel selectedStudent;
        public StudentModel SelectedStudent
        {
            get
            {
                return selectedStudent;
            }
            set
            {
                selectedStudent = value;
                if (selectedStudent != null)
                {
                    CanExecuteDeleteCommand = true;
                    CanExecuteModifyCommand = true;
                    choosedStudent = selectedStudent;
                }
                OnPropertyChanged("SelectedStudent");
            }
        }

        public bool CanExecuteDeleteCommand { get; set; }
        public bool CanExecuteModifyCommand { get; set; }

        public DisplayStudentsViewModel()
        {
            StudentsCollection = new ObservableCollection<StudentModel>(logicStudent.GetStudentModels());
        }

        private ICommand modificaStudentCommand;
        public ICommand ModificaStudentCommand
        {
            get
            {
                if (modificaStudentCommand == null)
                {
                    modificaStudentCommand = new RelayCommands(ModificaStudentMethod, param => CanExecuteModifyCommand);
                }
                return modificaStudentCommand;
            }
        }
        private void ModificaStudentMethod(object param)
        {
            UpdateStudent startWindow = new UpdateStudent();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = startWindow;
            startWindow.Show();
        }
        private ICommand stergeStudentCommand;
        public ICommand StergeStudentCommand
        {
            get
            {
                if (stergeStudentCommand == null)
                {
                    stergeStudentCommand = new RelayCommands(StergeStudentMethod, param => CanExecuteDeleteCommand);
                }
                return stergeStudentCommand;
            }
        }
        private void StergeStudentMethod(object param)
        {
            studentDb.spStudentDelete(selectedStudent.Id);
            MessageBox.Show("Ai sters studentul :" + SelectedStudent.Nume + " " + SelectedStudent.Prenume);
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
            MainWindow startWindow = new MainWindow();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = startWindow;
            startWindow.Show();
        }

        private ICommand addStudentsCommand;
        public ICommand AddStudentsCommand
        {
            get
            {
                addStudentsCommand = new RelayCommands(AddStudentsMethod);

                return addStudentsCommand;
            }
        }
        private void AddStudentsMethod(object param)
        {
            AddStudent addView = new AddStudent();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = addView;
            addView.Show();
        }
        
    }
}
