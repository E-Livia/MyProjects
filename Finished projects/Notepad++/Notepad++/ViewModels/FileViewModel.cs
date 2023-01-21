using Microsoft.Win32;
using Notepad__.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;

namespace Notepad__.ViewModels
{
    public class FileViewModel : ObservableObject
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
        public ObservableCollection<DocumentModel> Tabs { get; set; }
        private int contor = 0;

        //Toolbar commands
        public ICommand NewCommand { get; }
        public ICommand OpenCommand { get; }
        public ICommand SaveCommand { get; }
        public ICommand SaveAsCommand { get; }
        public ICommand ExitCommand { get; }
        public ICommand CloseFileCommand { get; }

        public FileViewModel(DocumentModel document)
        {
            _document = document;
            Tabs = new ObservableCollection<DocumentModel>();
            NewCommand = new RelayCommand(NewFile);
            OpenCommand = new RelayCommand(OpenFile);
            SaveCommand = new RelayCommand(SaveFile, () => !Document.isEmpty);
            SaveAsCommand = new RelayCommand(SaveFileAs);
            ExitCommand = new RelayCommand(ExitFile);
            CloseFileCommand = new RelayCommand(Remove); //pt inchiderea unui tab, neimplementat
            FindCommand = new RelayCommand(Find);
            ReplaceCommand = new RelayCommand(Replace);
            ReplaceAllCommand = new RelayCommand(ReplaceAll);
        }

        public void NewFile(object o)
        {
            contor++;
            DocumentModel tab = new DocumentModel()
            {
                FileName = "new file " + contor+ "*",
                Text = " "
            };

            Tabs.Add(tab);
        }

        public void OpenFile(object o)
        {
            var openFileDialog = new OpenFileDialog
            {
                DefaultExt = "*.txt",
                Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*"
            };

            if (openFileDialog.ShowDialog() == true)
            {
                DocumentModel tab = new DocumentModel();

                string fileName = openFileDialog.FileName;

                tab.FileName = Path.GetFileName(fileName); //obt numele
                tab.Text = File.ReadAllText(openFileDialog.FileName);
                tab.FilePAth = fileName;
                tab.FileName += "*";
                DockFile(openFileDialog);
                Document = tab;

                Tabs.Add(tab);
            }
        }

        public void SaveFile(object o)
        {
            DocumentModel doc = o as DocumentModel;
            File.WriteAllText(Document.FilePAth, doc.Text/*Document.Text*/);
            if (Document.FileName.Contains("*"))
            {
                doc.FileName = doc.FileName.Replace("*", "");
            }
        }

        public void SaveFileAs(object o) //tot nu salveaza textul
        {
            DocumentModel doc = o as DocumentModel;
            var saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Text File (*.txt)|*.txt";
            if (saveFileDialog.ShowDialog() == true)
            {
                DockFile(saveFileDialog);
                File.WriteAllText(saveFileDialog.FileName, Document.Text);
                if (Document.FileName.Contains("*"))
                {
                    doc.FileName = doc.FileName.Replace("*", "");
                }
            }
        }

        public void ExitFile(object o)
        {
            System.Windows.Application.Current.Shutdown();
        }

        public void Remove(object o)
        {
            //Tabs.RemoveAt(contor);
        }

        private void DockFile<T>(T dialog) where T : FileDialog
        {
            Document.FilePAth = dialog.FileName;
            Document.FileName = dialog.SafeFileName;
        }

        public ICommand FindCommand { get; }
        public ICommand ReplaceCommand { get; }
        public ICommand ReplaceAllCommand { get; }

        public void Find(object o)
        {
            var dialogBox = new DialogBox();
            string prop = "Word to find :";
            dialogBox.CreateDialogBox(prop);
            dialogBox.ShowDialog();
            var response = dialogBox.GetResponseTexts();
            for (int i = 0; i < Tabs.Count(); i++)
            {
                if (Tabs[i].Text.Contains(response))
                {
                    Tabs[i].Text = Tabs[i].Text.Replace(response, "|*" + response + "*|");
                }
            }
        }

        public void Replace(object o)
        {
            var dialogBox = new DialogBox();
            string prop = "Word to replace:";
            dialogBox.CreateDialogBox(prop);
            dialogBox.ShowDialog();
            var response = dialogBox.GetResponseTexts();
            string prop2 = "New word :";
            var dialogBox2 = new DialogBox();
            dialogBox2.CreateDialogBox(prop2);
            dialogBox2.ShowDialog();
            var response2 = dialogBox2.GetResponseTexts();
            for (int i = 0; i < Tabs.Count(); i++)
            {
                if (Tabs[i].Text.Contains(response))
                {
                    //Tabs[i].Text = "L-a gasit";
                    Tabs[i].Text = Tabs[i].Text.Replace(response, response2);
                    string name = Tabs[i].FileName;
                    if (name.Contains("*") == false)
                    { Tabs[i].FileName = Tabs[i].FileName + "*"; }
                }
                break;
            }
        }

        public void ReplaceAll(object o)
        {
            var dialogBox = new DialogBox();
            string prop = "Word to replace:";
            dialogBox.CreateDialogBox(prop);
            dialogBox.ShowDialog();
            var response = dialogBox.GetResponseTexts();
            string prop2 = "New word :";
            var dialogBox2 = new DialogBox();
            dialogBox2.CreateDialogBox(prop2);
            dialogBox2.ShowDialog();
            var response2 = dialogBox2.GetResponseTexts();
            for (int i = 0; i < Tabs.Count(); i++)
            {
                if (Tabs[i].Text.Contains(response))
                {
                    //Tabs[i].Text = "L-a gasit";
                    Tabs[i].Text = Tabs[i].Text.Replace(response, response2);
                    string name = Tabs[i].FileName;
                    if (name.Contains("*") == false)
                    { Tabs[i].FileName = Tabs[i].FileName + "*"; }
                }
            }
        }
    }
}