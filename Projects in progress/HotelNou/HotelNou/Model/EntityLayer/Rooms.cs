using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelNou.Model.EntityLayer
{
    public class Rooms : ObservableObject
    {
        private string tipCamera;
        public string Camera
        {
            get
            {
                return tipCamera;
            }
            set
            {
                OnPropertyChanged(ref tipCamera, value);
            }
        }

        private int nrCamere;
        public int NrCamere
        {
            get
            {
                return nrCamere;
            }
            set
            {
                OnPropertyChanged(ref nrCamere, value);
            }
        }
    }
}
