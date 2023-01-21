using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace HotelNou.Model
{
    public class ObservableObject : INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        //folosesc T (generic) pentru ca nu intotdeauna voi folosi acelasi tip de date
        //pot schimba un string, un int, o data etc
        public void OnPropertyChanged<T>(ref T property, T value, [CallerMemberName] string propertyName = "")
        {
            //whatever member is calling this specific method it's going to obtain its name
            //and that is why we are using the last parameter [CallerMemberName]
            //instead of using a magic string where we would normally type in ourselves the name of the property that needs to be updated
            //this is going to automatically grab whatever is calling this specific method and we will use that name
            property = value;
            var handler = PropertyChanged;
            if (handler != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
            }
        }

        public void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
