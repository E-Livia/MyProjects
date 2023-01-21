using StudentApp.Commands;
using StudentApp.View;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace StudentApp.ViewModel
{
    class MainWindowViewModel : BaseViewModel
    {
        private ICommand seeStudentCommand;
        public ICommand SeeStudentsCommand
        {
            get
            {
                seeStudentCommand = new RelayCommands(SeeStudentsMethod);

                return seeStudentCommand;
            }
        }
        private void SeeStudentsMethod(object param)
        {
            DisplayStudents seeView = new DisplayStudents();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = seeView;
            seeView.Show();

        }

        private ICommand seeProfCommand;
        public ICommand SeeProfCommand
        {
            get
            {
                seeProfCommand = new RelayCommands(SeeProfMethod);
                return seeProfCommand;
            }
        }
        private void SeeProfMethod(object param)
        {
            DisplayProfs seeView = new DisplayProfs();
            App.Current.MainWindow.Close();
            App.Current.MainWindow = seeView;
            seeView.Show();

        }
    }
}
