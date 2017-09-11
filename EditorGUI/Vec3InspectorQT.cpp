#include "Vec3InspectorQT.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <qvalidator.h>
#include "MathLib/Vec3.h"
#include "Vec3Helper.h"

namespace TCM
{
	namespace Editor
	{
		namespace QT
		{
			Vec3InspectorQT::Vec3InspectorQT( SerializedInterface* var ) :
			                                                             VarInspectorQT( var )
			{
				QDoubleValidator* validator = new QDoubleValidator( this );
				validator->setDecimals( 3 );
				int left, right;
				QHBoxLayout* layout = new QHBoxLayout();
				layout->getContentsMargins( &left, nullptr, &right, nullptr );
				layout->setContentsMargins( left / 2, 0, right / 2, 0 );

				m_x = new QLineEdit;
				m_x->setPlaceholderText( "X" );
				m_x->setValidator( validator );
				SetThirdMinSize( m_x );
				connect( m_x, SIGNAL( textEdited( const QString & ) ), this, SLOT( OnXChanged( const QString & ) ) );
				SetReadOnly( m_x, var->GetEditorType() == SerializedInterface::READONLY );

				m_y = new QLineEdit;
				m_y->setPlaceholderText( "Y" );
				m_y->setValidator( validator );
				SetThirdMinSize( m_y );
				connect( m_y, SIGNAL( textEdited( const QString & ) ), this, SLOT( OnYChanged( const QString & ) ) );
				SetReadOnly( m_y, var->GetEditorType() == SerializedInterface::READONLY );

				m_z = new QLineEdit;
				m_z->setPlaceholderText( "Z" );
				m_z->setValidator( validator );
				SetThirdMinSize( m_z );
				connect( m_z, SIGNAL( textEdited( const QString & ) ), this, SLOT( OnZChanged( const QString & ) ) );
				SetReadOnly( m_z, var->GetEditorType() == SerializedInterface::READONLY );

				layout->addWidget( m_x );
				layout->addWidget( m_y );
				layout->addWidget( m_z );

				m_widget = new QWidget;
				m_widget->setLayout( layout );

				m_validator = validator;
			}

			void Vec3InspectorQT::UpdateFromValue()
			{
				Engine::Math::Vec3 vec3 = Vec3Helper::Get( m_var );

				QString char_x = QString::number( vec3.x );
				m_validator->fixup( char_x );
				m_x->setText( char_x );
				QString char_y = QString::number( vec3.y );
				m_validator->fixup( char_y );
				m_y->setText( char_y );
				QString char_z = QString::number( vec3.z );
				m_validator->fixup( char_z );
				m_z->setText( char_z );
			}

			void Vec3InspectorQT::OnXChanged( const QString& text ) const
			{
				bool result;
				float value = text.toFloat( &result );
				if ( result )
					Vec3Helper::SetX( m_var, value );
			}

			void Vec3InspectorQT::OnYChanged( const QString& text ) const
			{
				bool result;
				float value = text.toFloat( &result );
				if ( result )
					Vec3Helper::SetY( m_var, value );
			}

			void Vec3InspectorQT::OnZChanged( const QString& text ) const
			{
				bool result;
				float value = text.toFloat( &result );
				if ( result )
					Vec3Helper::SetZ( m_var, value );
			}

			void Vec3InspectorQT::SetThirdMinSize( QWidget* widget ) const
			{
				widget->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Preferred );
				widget->setMinimumWidth( widget->minimumWidth() / 3 );
			}
		}
	}
}