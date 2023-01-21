using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace Notepad__
{
    /// <summary>
    /// Interaction logic for DialogBox.xaml
    /// </summary>
    public partial class DialogBox : Window
    {
        public DialogBox()
        {
            InitializeComponent();
        }

        public string GetResponseTexts()
        {
            IEnumerable<TextBox> textBoxes = mainGrid.Children.OfType<TextBox>();
            string response = null;
            foreach (var textBox in textBoxes)
            {
                if (textBox.Text.Length == 0)
                    response = ".";
                else
                    response = textBox.Text;
            }

            return response;
        }

        public void CreateDialogBox(string value)
        {
            /*First, we need to set the height of the window:
             for each text we need a TextBlock(22) and a TextBox(22)=> 40
             for ok button we have 50 
             so the heright of the window must be number of texts * 2 * 22 + 50.*/
            int index = 1;
            var textBlock = new TextBlock();
            textBlock.Text = value;
            mainGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            var textBox = new TextBox();
            mainGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(textBlock, index++);
            mainGrid.Children.Add(textBlock);
            Grid.SetRow(textBox, index++);
            mainGrid.Children.Add(textBox);

        }

        private void OKButton_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            dialogBoxWindow.Close();
        }
    }
}
