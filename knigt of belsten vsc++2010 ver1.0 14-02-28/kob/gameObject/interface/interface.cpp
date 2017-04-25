#include "interface.h"

Interface::Interface()
{

}

Interface::~Interface()
{
	m_spGraph2D_HpGauge.reset();
	m_spGraph2D_HpPoint.reset();

	m_spDrawBuffer.reset();

}

void Interface::initialize(sp_DrawBuffer spDrawBuffer)
{
//	++spDrawBuffer;
//	++m_spGraph2D_HpGauge;
//	++m_spGraph2D_HpPoint;
	
	m_spDrawBuffer=spDrawBuffer;

	if(m_spGraph2D_HpGauge.get()==NULL)
	{
		m_spGraph2D_HpGauge=sp_Graphics2D(new Graphics2D());

		if(m_spGraph2D_HpGauge.get()!=NULL)
		{
			m_spGraph2D_HpGauge->initialize("images/interface/gauge.png");
		}
	}

	if(m_spGraph2D_HpPoint.get()==NULL)
	{
		m_spGraph2D_HpPoint=sp_Graphics2D(new Graphics2D());
		if(m_spGraph2D_HpPoint.get()!=NULL)
		{
			m_spGraph2D_HpPoint->initialize("images/interface/point.png");
		}
	}
}

void Interface::DrawHpGauge(int point, int maxPoint)
{
	double point_d =static_cast<double>(point);
	double rate =(point_d/maxPoint)*100;//パーセント

	int max=static_cast<int>(rate);

	if(m_spDrawBuffer.get()!=NULL)
	{
		if(m_spGraph2D_HpGauge.get()!=NULL)
		{
			if(m_spGraph2D_HpGauge->isInitialized())
			{
				m_spDrawBuffer->DrawSet(m_spGraph2D_HpGauge.get(),0,10,10,false);
			}
		}
		
		if(m_spGraph2D_HpPoint.get()!=NULL)
		{
			if(m_spGraph2D_HpPoint->isInitialized())
			{
				for(int i=0;i<max;i++)
				{
					m_spDrawBuffer->DrawSet(m_spGraph2D_HpPoint.get(),0,10+3+2*i,10+3,0,false);
				}
			}
		}
	}	
}


