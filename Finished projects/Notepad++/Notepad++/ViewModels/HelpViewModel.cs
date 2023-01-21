using Notepad__.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Notepad__.ViewModels
{
    public class HelpViewModel : ObservableObject
    {
        public ICommand HelpCommand { get; }
        public DocumentModel Document { get; set; }

        public HelpViewModel()
        {
            HelpCommand = new RelayCommand(DisplayAbout);
        }

        private void DisplayAbout(object o)
        {
            var helpDialog = new HelpDialog();
            helpDialog.DataContext = Document;
            helpDialog.ShowDialog();
        }
    }
}
