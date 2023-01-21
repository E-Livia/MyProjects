using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelNou.Model.EntityLayer
{
    public class Employee : ObservableObject
    {
        private int? employeeID;
        public int? EmployeeID
        {
            get
            {
                return employeeID;
            }
            set
            {
                OnPropertyChanged(ref employeeID, value);
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

        private long cnp;
        public long CNP
        {
            get
            {
                return cnp;
            }
            set
            {
                OnPropertyChanged(ref cnp, value);
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

        private string emailAddress;
        public string EmailAddress
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

        private DateTime dateOfEmployment;
        public DateTime DateOfEmployment
        {
            get
            {
                return dateOfEmployment;
            }
            set
            {
                OnPropertyChanged(ref dateOfEmployment, value);
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

        private bool role;
        public bool Role
        {
            get
            {
                return role;
            }
            set
            {
                OnPropertyChanged(ref role, value);
            }
        }
    }
}
