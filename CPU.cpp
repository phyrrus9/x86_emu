typedef unsigned int bit_xx_reg;

typedef enum
{
	fCF = (1 << 0),  fPF = (1 << 1),  fAF = (1 << 4),
	fXF = (1 << 6),  fSF = (1 << 7),  fTF = (1 << 8),
	fIF = (1 << 9),  fDF = (1 << 10), fOF = (1 << 11),
	fNT = (1 << 14), fRF = (1 << 16), fVN = (1 << 17),
	fAC = (1 << 18), fVIF= (1 << 19), fVIP= (1 << 20),
	fID = (1 << 21), fALL= (1 << 31) /*fALL is not real*/
} flag_specifier;

typedef enum
{
	rEAX, rEBX, rECX, rEDX,
	rAX,  rBX,  rCX,  rDX,
	rAH,  rAL,  rBH,  rBL,
	rCH,  rCL,  rDH,  rDL,
	rCS,  rDS,  rES,  rFS,
	rGS,  rSS,  rDI,  rSI,
	rBP,  rSP,  rIP
} reg_specifier;

unsigned char reg_not_found;

typedef union
{
	unsigned int bit_32;
	unsigned short bit_16[2];
	unsigned char bit_08[4];
} register_type;

class register_state_fl
{
protected:
	unsigned int FL;
public:
	register_state_fl()
	{	}
	~register_state_fl()
	{	}
	bit_xx_reg get(flag_specifier s)
	{
		switch (s)
		{
			case fCF : return (FL & fCF ); break;
			case fPF : return (FL & fPF ); break;
			case fAF : return (FL & fAF ); break;
			case fXF : return (FL & fXF ); break;
			case fSF : return (FL & fSF ); break;
			case fTF : return (FL & fTF ); break;
			case fIF : return (FL & fIF ); break;
			case fDF : return (FL & fDF ); break;
			case fOF : return (FL & fOF ); break;
			case fNT : return (FL & fNT ); break;
			case fRF : return (FL & fRF ); break;
			case fVN : return (FL & fVN ); break;
			case fAC : return (FL & fAC ); break;
			case fVIF: return (FL & fVIF); break;
			case fVIP: return (FL & fVIP); break;
			case fID : return (FL & fID ); break;
			case fALL: return FL         ; break;
			default  : reg_not_found = 1;
		}
		return 0;
	}
#define R_SET(s) { if (r) FL |= s; else if (get(s)) FL ^ s; }
	void set(flag_specifier s, unsigned char r)
	{
		switch (s)
		{
			case fCF : R_SET(fCF);  break;
			case fPF : R_SET(fPF);  break;
			case fAF : R_SET(fAF);  break;
			case fXF : R_SET(fXF);  break;
			case fSF : R_SET(fSF);  break;
			case fTF : R_SET(fTF);  break;
			case fIF : R_SET(fIF);  break;
			case fDF : R_SET(fDF);  break;
			case fOF : R_SET(fOF);  break;
			case fNT : R_SET(fNT);  break;
			case fRF : R_SET(fRF);  break;
			case fVN : R_SET(fVN);  break;
			case fAC : R_SET(fAC);  break;
			case fVIF: R_SET(fVIF); break;
			case fVIP: R_SET(fVIP); break;
			case fID : R_SET(fID);  break;
			default  : reg_not_found = 1;
		}
	}
#undef R_SET
	void set(unsigned int r)
	{
		FL = r;
	}
};

class register_state_gp
{
protected:
	register_type EAX, EBX, ECX, EDX;
public:
	register_state_gp()
	{	}
	~register_state_gp()
	{	}
	bit_xx_reg get(reg_specifier s)
	{
		switch (s)
		{
			case rEAX: return EAX.bit_32;    break;
			case rEBX: return EBX.bit_32;    break;
			case rECX: return ECX.bit_32;    break;
			case rEDX: return EDX.bit_32;    break;
			case rAX : return EAX.bit_16[0]; break;
			case rBX : return EBX.bit_16[0]; break;
			case rCX : return ECX.bit_16[0]; break;
			case rDX : return EDX.bit_16[0]; break;
			case rAH : return EAX.bit_08[1]; break;
			case rAL : return EAX.bit_08[0]; break;
			case rBH : return EBX.bit_08[1]; break;
			case rBL : return EBX.bit_08[0]; break;
			case rCH : return ECX.bit_08[1]; break;
			case rCL : return ECX.bit_08[0]; break;
			case rDH : return EDX.bit_08[1]; break;
			case rDL : return EDX.bit_08[0]; break;
			default  : reg_not_found = 1;
		}
		return 0;
	}

	void set(reg_specifier s, bit_xx_reg r)
	{
		switch (s)
		{
			case rAX:  EAX.bit_16[0] = r; break;
			case rAH:  EAX.bit_08[1] = r; break;
			case rAL:  EAX.bit_08[0] = r; break;
			case rEAX: EAX.bit_32 = r; break;
			case rBX:  EBX.bit_16[0] = r; break;
			case rBH:  EBX.bit_08[1] = r; break;
			case rBL:  EBX.bit_08[0] = r; break;
			case rEBX: EBX.bit_32 = r; break;
			case rCX:  ECX.bit_16[0] = r; break;
			case rCH:  ECX.bit_08[1] = r; break;
			case rCL:  ECX.bit_08[0] = r; break;
			case rECX: ECX.bit_32 = r; break;
			case rDX:  EDX.bit_16[0] = r; break;
			case rDH:  EDX.bit_08[1] = r; break;
			case rDL:  EDX.bit_08[0] = r; break;
			case rEDX: EDX.bit_32 = r; break;
			default  : reg_not_found = 1;
		}

	}
};

class register_state_seg
{
protected:
	register_type CS, DS, ES, FS, GS, SS;
public:
	register_state_seg()
	{	}
	~register_state_seg()
	{	}
	bit_xx_reg get(reg_specifier s)
	{
		switch (s)
		{
			case rCS : return CS.bit_16[0]; break;
			case rDS : return DS.bit_16[0]; break;
			case rES : return ES.bit_16[0]; break;
			case rFS : return FS.bit_16[0]; break;
			case rGS : return GS.bit_16[0]; break;
			case rSS : return SS.bit_16[0]; break;
		}
		return 0;
	}

	void set(reg_specifier s, bit_xx_reg r)
	{
		switch (s)
		{
			case rCS:  CS.bit_16[0] = r; break;
			case rDS:  DS.bit_16[0] = r; break;
			case rES:  ES.bit_16[0] = r; break;
			case rFS:  FS.bit_16[0] = r; break;
			case rGS:  GS.bit_16[0] = r; break;
			case rSS:  SS.bit_16[0] = r; break;
			default  : reg_not_found = 1;
		}

	}
};


class register_state_ind
{
protected:
	register_type DI, SI, BP, SP, IP;
public:
	register_state_ind()
	{	}
	~register_state_ind()
	{	}
	bit_xx_reg get(reg_specifier s)
	{
		switch (s)
		{
			case rDI : return DI.bit_16[0]; break;
			case rSI : return SI.bit_16[0]; break;
			case rBP : return BP.bit_16[0]; break;
			case rSP : return SP.bit_16[0]; break;
			case rIP : return IP.bit_16[0]; break;
		}
		return 0;
	}

	void set(reg_specifier s, bit_xx_reg r)
	{
		switch (s)
		{
			case rDI:  DI.bit_16[0] = r; break;
			case rSI:  SI.bit_16[0] = r; break;
			case rBP:  BP.bit_16[0] = r; break;
			case rSP:  SP.bit_16[0] = r; break;
			case rIP:  IP.bit_16[0] = r; break;
			default  : reg_not_found = 1;
		}

	}
};

class register_state
{
protected:
	register_state_gp  *gp;
	register_state_seg *seg;
	register_state_ind *ind;
	register_state_fl  *fl;
public:
	register_state()
	{
		gp  = new register_state_gp ();
		seg = new register_state_seg();
		ind = new register_state_ind();
		fl  = new register_state_fl ();
	}
	~register_state()
	{
		delete gp;
		delete seg;
		delete ind;
		delete fl;
	}
	bit_xx_reg get(flag_specifier r)
	{
		bit_xx_reg ret;
		reg_not_found = 0;
		ret = fl->get(r);
		return ret;
	}
	bit_xx_reg get(reg_specifier r)
	{
		bit_xx_reg ret;
		reg_not_found = 0;
		ret = gp->get(r);
		if (reg_not_found)
		{
			ret = seg->get(r);
			if (reg_not_found)
				ret = ind->get(r);
		}
		return ret;
	}
	void set(flag_specifier r, unsigned char d)
	{
		reg_not_found = 0;
		fl->set(r, d);
	}
	void set(reg_specifier r, bit_xx_reg d)
	{
		reg_not_found = 0;
		gp->set(r, d);
		if (reg_not_found)
		{
			seg->set(r, d);
			if (reg_not_found)
				ind->set(r, d);
		}
	}
};
