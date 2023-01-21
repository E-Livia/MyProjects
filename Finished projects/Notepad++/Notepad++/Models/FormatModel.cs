using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;

namespace Notepad__.Models
{
    public class FormatModel : ObservableObject
    {
        private FontStyle _style;
        public FontStyle Style
        {
            get
            {
                return _style;
            }
            set
            {
                OnPropertyChanged(ref _style, value);
            }
        }

        private FontStyle _weight;
        public FontStyle Weight
        {
            get
            {
                return _weight;
            }
            set
            {
                OnPropertyChanged(ref _weight, value);
            }
        }

        private FontStyle _family;
        public FontStyle Family
        {
            get
            {
                return _family;
            }
            set
            {
                OnPropertyChanged(ref _family, value);
            }
        }

        private double _size;
        public double Size
        {
            get
            {
                return _size;
            }
            set
            {
                OnPropertyChanged(ref _size, value);
            }
        }
    }
}
