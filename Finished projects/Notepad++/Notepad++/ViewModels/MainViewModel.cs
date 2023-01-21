using Notepad__.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Notepad__.ViewModels
{
    //we are using this class because we want all of our commands to refer at the same document
    public class MainViewModel : ObservableObject
    {
        private DocumentModel _document;
        public DocumentModel Document
        {
            get
            {
                return _document;
            }
            set
            {
                OnPropertyChanged(ref _document, value);
            }
        }

        public EditorViewModel Editor { get; set; }

        public FileViewModel File { get; set; }

        public SearchViewModel Search { get; set; }

        public HelpViewModel Help { get; set; }

        public MainViewModel()
        {
            Document = new DocumentModel();
            Help = new HelpViewModel();
            Editor = new EditorViewModel(Document);
            File = new FileViewModel(Document);
            Search = new SearchViewModel(Document);
        }
    }
}
