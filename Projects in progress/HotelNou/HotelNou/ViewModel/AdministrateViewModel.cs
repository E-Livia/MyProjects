using HotelNou.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;

namespace HotelNou.ViewModel
{
    public class AdministrateViewModel : ObservableObject
    {
        HotelTransilvaniaEntities hotel = new HotelTransilvaniaEntities();
        public ICommand AddRoomCommand { get; }
        public ICommand UpdateRoomCommand { get; }
        public ICommand AddFeatureCommand { get; }

        public AdministrateViewModel()
        {
            AddRoomCommand = new RelayCommand(AddRoom);
            UpdateRoomCommand = new RelayCommand(UpdateRoom);
            AddFeatureCommand = new RelayCommand(AddFeature);
        }

        #region prop
        private string roomType;
        public string RoomType
        {
            get
            {
                return roomType;
            }
            set
            {
                OnPropertyChanged(ref roomType, value);
            }
        }
        private int roomNo;
        public int RoomNo
        {
            get
            {
                return roomNo;
            }
            set
            {
                OnPropertyChanged(ref roomNo, value);
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

        private string feature;
        public string Feature
        {
            get
            {
                return feature;
            }
            set
            {
                OnPropertyChanged(ref feature, value);
            }
        }
        #endregion

        private void AddRoom(object o)
        {
            hotel.AddRoom(RoomType, RoomNo);
            MessageBox.Show("Succes!");
        }

        private void UpdateRoom(object o)
        {
            hotel.UpdateRoom(RoomID, RoomType, RoomNo);
            MessageBox.Show("Succes!");
        }

        private void AddFeature(object o)
        {
            hotel.AddFeature(Feature);
            MessageBox.Show("Succes!");
        }
    }
}
