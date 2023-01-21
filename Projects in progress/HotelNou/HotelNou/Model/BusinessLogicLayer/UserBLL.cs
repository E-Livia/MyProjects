using HotelNou.Model.EntityLayer;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace HotelNou.Model.BusinessLogicLayer
{
    class UserBLL
    {
        public List<User> GetUsersMenu()
        {
            var productQuery = (from user in hotel.Clientis
                                where user.username.Contains("client")
                                select new User()
                                {
                                    Name = user.nume_client,
                                    EmailAddress = (int)user.adresa_email

                                }).ToList();

            return productQuery;
        }

        private HotelTransilvaniaEntities hotel = new HotelTransilvaniaEntities();
        public bool SignUp(string name, int phoneNo, int email, string username, string password)
        {
            var query = (from user in hotel.Clientis select user)?.ToList();
            foreach (var userInList in query)
            {
                if (userInList.adresa_email.Equals(email))
                {
                    return false;
                }
            }

            hotel.Clientis.Add(new Clienti()
            {
                nume_client = name,
                nr_telefon = phoneNo,
                adresa_email = email,
                username = username,
                parola = password,
            });
            hotel.SaveChanges();

            return true;
        }

        public bool SignIn(string username, string password)
        {
            try
            {
                var query = (from user in hotel.Clientis
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
