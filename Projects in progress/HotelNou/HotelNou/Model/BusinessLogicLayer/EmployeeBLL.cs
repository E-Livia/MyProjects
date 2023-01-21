using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelNou.Model.BusinessLogicLayer
{
    public class EmployeeBLL 
    {
        private HotelTransilvaniaEntities hotel = new HotelTransilvaniaEntities();
        public bool SignIn(string username,string password)
        {
            try
            {
                var query = (from user in hotel.Angajatis
                             where user.username.Equals(username) && user.parola.Equals(password)
                             select user).First();
            }
            catch
            {
                return false;
            }
            return true;
        }
    }
}
