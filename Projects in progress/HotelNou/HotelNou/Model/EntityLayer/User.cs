using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelNou.Model.EntityLayer
{
    public class User : ObservableObject
    {
        private int? userID;
        public int? UserID
        {
            get
            {
                return userID;
            }
            set
            {
                OnPropertyChanged(ref userID, value);
            }
        }

        private string name;
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                OnPropertyChanged(ref name, value);
            }
        }

        private int phoneNo;
        public int PhoneNo
        {
            get
            {
                return phoneNo;
            }
            set
            {
                OnPropertyChanged(ref phoneNo, value);
            }
        }

        private int emailAddress;
        public int EmailAddress
        {
            get
            {
                return emailAddress;
            }
            set
            {
                OnPropertyChanged(ref emailAddress, value);
            }
        }

        private string username;
        public string Username
        {
            get
            {
                return username;
            }
            set
            {
                OnPropertyChanged(ref username, value);
            }
        }

        private string password;
        public string Password
        {
            get
            {
                return password;
            }
            set
            {
                OnPropertyChanged(ref password, value);
            }
        }
    }
}
