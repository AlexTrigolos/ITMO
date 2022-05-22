import { ApiProperty } from '@nestjs/swagger';
import { ValidateIf } from 'class-validator';

export class CreateMyPostDto {
  @ApiProperty()
  @ValidateIf((object, value) => value !== undefined)
  title: string;

  @ApiProperty({ required: false })
  @ValidateIf((object, value) => value !== undefined)
  content?: string;

  @ApiProperty({ required: false })
  @ValidateIf((object, value) => value !== undefined)
  authorId?: number;
}
