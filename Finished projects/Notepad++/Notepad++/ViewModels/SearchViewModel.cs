using Notepad__.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Notepad__.ViewModels
{
    public class SearchViewModel
    {
        public DocumentModel Document { get; set; }

        public SearchViewModel(DocumentModel document)
        {
            Document = document;
        }
        //to do
        //public ICommand FindCommand { get; }
        //public ICommand ReplaceCommand { get; }
        //public ICommand ReplaceAllCommand { get; }

        //public void Find(object o)
        //{
        //    var dialogBox = new DialogBox();
        //    string prop = "Word to find :";
        //    dialogBox.CreateDialogBox(prop);
        //    dialogBox.ShowDialog();
        //    var response = dialogBox.GetResponseTexts();
        //    for (int i = 0; i < Tabs.Count(); i++)
        //    {
        //        if (Tabs[i].Text.Contains(response))
        //        {
        //            Tabs[i].Text = Tabs[i].Text.Replace(response, "!$!" + response + "!$!");
        //        }
        //    }
        //}

        //public void Replace(object o)
        //{

        //}

        //public void ReplaceAll(object o)
        //{

        //}
    }
}
