using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Serialization;

namespace Hangman.Model
{
    [Serializable]
    public class Words
    {
        [XmlArray]
        public ObservableCollection<string> Cars { get; set; } = new ObservableCollection<string>();
        [XmlArray]
        public ObservableCollection<string> Movies { get; set; } = new ObservableCollection<string>();
        [XmlArray]
        public ObservableCollection<string> Countries { get; set; } = new ObservableCollection<string>();
        [XmlArray]
        public ObservableCollection<string> Flowers { get; set; } = new ObservableCollection<string>();
        [XmlArray]
        public ObservableCollection<string> Animals { get; set; } = new ObservableCollection<string>();
    
        public Words()
        {
            Cars.Add("VOLKSWAGEN");
            Cars.Add("BMW");
            Cars.Add("MERCEDES BENZ");
            Cars.Add("AUDI");
            Cars.Add("MAZDA");
            Cars.Add("SKODA");
            Cars.Add("RENAULT");
            Cars.Add("OPEL");
            Cars.Add("KIA");
            Cars.Add("TOYOTA");
            Cars.Add("VOLVO");
            Cars.Add("PEUGEOT");
            Cars.Add("MITSUBISHI");
            Cars.Add("SUZUKI");
            Cars.Add("HYUNDAI");
            Cars.Add("NISSAN");
            Cars.Add("PORCHE");

            Movies.Add("BOYKA");
            Movies.Add("VENOM");
            Movies.Add("FINDING NEMO");
            Movies.Add("SPIDERMAN NO WAY HOME");
            Movies.Add("WONDER WOMAN");
            Movies.Add("PEAKY BLINDERS");
            Movies.Add("LUCIFER");
            Movies.Add("JUMAJI");
            Movies.Add("THE EQUALIZER");
            Movies.Add("CITY OF BONES");
            Movies.Add("JOHN WICK");
            Movies.Add("UNCHARTED");
            Movies.Add("EUPHORIA");
            Movies.Add("BRIGHT");
            Movies.Add("THE PURGE");
            Movies.Add("PIRATES OF THE CARIBBEAN");

            Countries.Add("CANADA");
            Countries.Add("BRAZILIA");
            Countries.Add("ALGERIA");
            Countries.Add("ROMANIA");
            Countries.Add("PORTUGALIA");
            Countries.Add("PAKISTAN");
            Countries.Add("BOTSWANA");
            Countries.Add("KENYA");
            Countries.Add("FRANTA");
            Countries.Add("GERMANIA");
            Countries.Add("NORVEGIA");
            Countries.Add("GUATEMALA");
            Countries.Add("SRI LANKA");
            Countries.Add("BOSNIA SI HERTOGOVINA");
            Countries.Add("SLOVACIA");
            Countries.Add("SLOVENIA");
            Countries.Add("LETONIA");
            Countries.Add("LITUANIA");
            Countries.Add("TARILE DE JOS");
            Countries.Add("MACEDONIA DE NORD");

            Flowers.Add("LALEAUA PESTRITA");
            Flowers.Add("BRANDUSA DE PRIMAVARA");
            Flowers.Add("MARGARITAR");
            Flowers.Add("BEGONIA");
            Flowers.Add("REGINA NOPTII");
            Flowers.Add("MARGARETA");
            Flowers.Add("PANSELUTA");
            Flowers.Add("MAGNOLIA");
            Flowers.Add("HORTENSIA");
            Flowers.Add("ORHIDEE");
            Flowers.Add("GLADIOLA");
            Flowers.Add("BRANDUSA DE MUNTE");
            Flowers.Add("ANEMONA");
            Flowers.Add("CAPRIFOI");
            Flowers.Add("ERANTHIS");
            Flowers.Add("CLEMATITA TETRAROSE");
            Flowers.Add("NARCISA");
            Flowers.Add("ZAMBILA STRUGURAS");
            Flowers.Add("GLICINA ALBA");
            Flowers.Add("TROIENE DE ZAPADA");
            Flowers.Add("CRIN TIGRAT");
            Flowers.Add("DALIA VULCAN");
            Flowers.Add("STEA STRALUCITOARE");

            Animals.Add("ARICI");
            Animals.Add("BIBILICA");
            Animals.Add("BIVOL");
            Animals.Add("CAINE");
            Animals.Add("CURCAN");
            Animals.Add("EMU");
            Animals.Add("FAZAN");
            Animals.Add("LEBADA");
            Animals.Add("GAINA JAPONEZA");
            Animals.Add("PAPAGAL CACADU UMBRELAT ALB");
            Animals.Add("PORCUSOR DE GUINEEA");
            Animals.Add("VEVERITA");
            Animals.Add("HARCIOG");
            Animals.Add("DIHOR");
            Animals.Add("PISICA SALBATICA");
            Animals.Add("CHITCAN DE APA");
            Animals.Add("ZIMBRU");
            Animals.Add("CASTOR");
            Animals.Add("VULPE");
            Animals.Add("VEVERITA");
            Animals.Add("COIOT");
            Animals.Add("ANTILOPA KONGONI");
            Animals.Add("PUFFIN");
            Animals.Add("DIAVOLUL TAZMANIAN");
        }
    }
}
