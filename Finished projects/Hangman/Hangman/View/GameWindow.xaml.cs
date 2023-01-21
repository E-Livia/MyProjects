using Hangman.Model;
using Hangman.Services;
using Hangman.ViewModel;
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

namespace Hangman.View
{
    /// <summary>
    /// Interaction logic for GameWindow.xaml
    /// </summary>
    public partial class GameWindow : Window
    {
        public GameWindow()
        {
            Serialization actions = new Serialization();
            Words words = new Words();
            actions.SerializeWords("./../../Xml/Words.xml", words);
            InitializeComponent();
        }

        public GameWindow(GameViewModel game)
        {
            InitializeComponent();
            DataContext = game;
        }
    }
}
