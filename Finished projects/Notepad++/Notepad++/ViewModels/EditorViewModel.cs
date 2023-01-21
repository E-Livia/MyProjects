using Notepad__.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Notepad__.ViewModels
{
    public class EditorViewModel
    {
        public ICommand FormatCommand { get; }
        public FormatModel Format { get; set; }
        public DocumentModel Document { get; set; }

        public EditorViewModel(DocumentModel document)
        {
            Document = document;
            Format = new FormatModel();
            FormatCommand = new RelayCommand(OpenStyleDialog);
        }

        private void OpenStyleDialog(object o)
        {
            var fontDialog = new FormatDialog();
            fontDialog.DataContext = Format;
            fontDialog.ShowDialog();
        }
    }
}
