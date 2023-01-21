using Hangman.Model;
using Hangman.ViewModel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Hangman.Services
{
    class Serialization
    {
        public void SerializeUsers(string xmlFileName, SignInViewModel entity)
        {
            XmlSerializer xmlser = new XmlSerializer(typeof(SignInViewModel));
            FileStream fileStr = new FileStream(xmlFileName, FileMode.Create);
            xmlser.Serialize(fileStr, entity);
            fileStr.Dispose();
        }

        public void SerializeWords(string xmlFileName, Words entity)
        {
            XmlSerializer xmlser = new XmlSerializer(typeof(Words));
            FileStream fileStr = new FileStream(xmlFileName, FileMode.Create);
            xmlser.Serialize(fileStr, entity);
            fileStr.Dispose();
        }

        public SignInViewModel DeserializeUsers(string xmlFileName)
        {
            XmlSerializer xmlser = new XmlSerializer(typeof(SignInViewModel));
            FileStream file = new FileStream(xmlFileName, FileMode.Open);
            var entity = xmlser.Deserialize(file);
            file.Dispose();
            return entity as SignInViewModel;
        }
        public Words DeserializeWords(string xmlFileName)
        {
            XmlSerializer xmlser = new XmlSerializer(typeof(Words));
            FileStream file = new FileStream(xmlFileName, FileMode.Open);
            var entity = xmlser.Deserialize(file);
            file.Dispose();
            return entity as Words;
        }
    }
}
