#include <iostream>
#include <algorithm>

class Razlomak
{
public:
	Razlomak() {}
	Razlomak(int brojnik, int nazivnik) { m_brojnik = brojnik; m_nazivnik = nazivnik; }

	void ispisi() { std::cout << m_brojnik << "/" << m_nazivnik << "\n"; }

	/*//////////////////////////////////////////////////////////////////////////////////////////////////////
	//		Znak ! ispred Razloma() prije nego sto se natrag salje krati razlomak preko operator!()-a
	*///////////////////////////////////////////////////////////////////////////////////////////////////////
	Razlomak operator+(const Razlomak& r)
	{
		if (r.m_nazivnik == this->m_nazivnik) { return Razlomak(r.m_brojnik + this->m_brojnik, r.m_nazivnik); }
		else
		{
			int nazivnik	= r.m_nazivnik * this->m_nazivnik;
			int brojnik		= (m_brojnik * (nazivnik / m_nazivnik)) + (r.m_brojnik * (nazivnik / r.m_nazivnik));

			return !Razlomak(brojnik, nazivnik);
		}
	}

	Razlomak operator-(const Razlomak& r)
	{
		if (r.m_nazivnik == this->m_nazivnik) { return Razlomak(r.m_brojnik - this->m_brojnik, r.m_nazivnik); }
		else
		{
			int nazivnik	= r.m_nazivnik * this->m_nazivnik;
			int brojnik		= (m_brojnik * (nazivnik / m_nazivnik)) - (r.m_brojnik * (nazivnik / r.m_nazivnik));

			return !Razlomak(brojnik, nazivnik);
		}
	}

	void operator+=(const Razlomak& r)
	{
		if (r.m_nazivnik == this->m_nazivnik) { *this = Razlomak(r.m_brojnik + this->m_brojnik, r.m_nazivnik); }
		else
		{
			int nazivnik = r.m_nazivnik * this->m_nazivnik;
			int brojnik = (m_brojnik * (nazivnik / m_nazivnik)) + (r.m_brojnik * (nazivnik / r.m_nazivnik));

			*this = !Razlomak(brojnik, nazivnik);
		}
	}

	void operator-=(const Razlomak& r)
	{
		if (r.m_nazivnik == this->m_nazivnik) { *this = Razlomak(r.m_brojnik - this->m_brojnik, r.m_nazivnik); }
		else
		{
			int nazivnik = r.m_nazivnik * this->m_nazivnik;
			int brojnik = (m_brojnik * (nazivnik / m_nazivnik)) - (r.m_brojnik * (nazivnik / r.m_nazivnik));

			*this = !Razlomak(brojnik, nazivnik);
		}
	}

	Razlomak operator*(const Razlomak& r) { return !Razlomak(r.m_brojnik * this->m_brojnik, r.m_nazivnik * this->m_nazivnik); }
	Razlomak operator/(const Razlomak& r) { return !Razlomak(this->m_brojnik * r.m_nazivnik, this->m_nazivnik * r.m_brojnik); }

	void operator*=(const Razlomak& r) { this->m_brojnik *= r.m_brojnik; this->m_nazivnik *= r.m_nazivnik; !*this; }
	void operator/=(const Razlomak& r) { this->m_brojnik *= r.m_nazivnik; this->m_nazivnik *= r.m_brojnik; !*this; }
	
	/*//////////////////////////////
	//		Skrati Razlomak
	*///////////////////////////////
	Razlomak operator!()
	{
		if (this->m_brojnik % this->m_nazivnik == 0) { this->m_brojnik /= this->m_nazivnik;this->m_nazivnik = 1; }
		else
		{
			// Naði da koji dio razlomka je manji od drugog
			int min = std::min(this->m_brojnik, this->m_nazivnik);

			// Pocni traziti zajednicki dijeljitelj od 2 i trazi dok nije i = djelu razlomka koji je manji od drugog
			for (int i = 2; i <= std::abs(min); i++)
			{
				if (this->m_brojnik % i == 0 && this->m_nazivnik % i == 0)
				{
					this->m_brojnik /= i;
					this->m_nazivnik /= i;
					
					// Resetiraj i probaj opet skratiti razlomak
					operator!();
				}
			}
		}

		return *this;
	}

private:
	int m_brojnik, m_nazivnik;
};

int main()
{
	Razlomak a(1, 2);
	Razlomak b(2, 8);

	Razlomak c = a + b;
	c.ispisi();

	Razlomak d(84, 26);
	!d;
	d.ispisi();

	a += b;
	a.ispisi();

	std::cout << "\n";
	system("pause");
	return 0;
}