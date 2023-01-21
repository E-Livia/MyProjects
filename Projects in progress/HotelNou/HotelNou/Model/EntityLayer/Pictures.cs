using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelNou.Model.EntityLayer
{
    public class Pictures : ObservableObject
    {
        private string imgPath;
        public string ImgPath
        {
            get
            {
                return imgPath;
            }
            set
            {
                OnPropertyChanged(ref imgPath, value);
            }
        }

        private int roomID;
        public int RoomID
        {
            get
            {
                return roomID;
            }
            set
            {
                OnPropertyChanged(ref roomID, value);
            }
        }
    }
}
